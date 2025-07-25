#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>
#include <zephyr/fs/nvs.h>

#include <zephyr/pm/pm.h>

LOG_MODULE_REGISTER(main);

static const struct device *imu = DEVICE_DT_GET_ANY(st_lsm6dsl);

#define NVS_PARTITION		    storage_partition
#define NVS_PARTITION_DEVICE	FIXED_PARTITION_DEVICE(NVS_PARTITION)
#define NVS_PARTITION_OFFSET	FIXED_PARTITION_OFFSET(NVS_PARTITION)


void init_imu(void) {
    struct sensor_value odr_attr;
    odr_attr.val1 = 104;
	odr_attr.val2 = 0;
	if (sensor_attr_set(imu, SENSOR_CHAN_ACCEL_XYZ,
			    SENSOR_ATTR_SAMPLING_FREQUENCY, &odr_attr) < 0) {
		printk("Cannot set sampling frequency for accelerometer.\n");
		return ;
	}

	if (sensor_attr_set(imu, SENSOR_CHAN_GYRO_XYZ,
			    SENSOR_ATTR_SAMPLING_FREQUENCY, &odr_attr) < 0) {
		printk("Cannot set sampling frequency for gyro.\n");
		return ;
	}
}

// static const struct device *imu = DEVICE_DT_GET(DT_ALIAS(imu));
struct sensor_value temp;
struct sensor_value accel[3], gyro[3];
void read_imu(void) {
    if (!device_is_ready(imu)) {
        LOG_ERR("IMU not ready");
        return;
    }

    int rc = sensor_sample_fetch(imu);
    if (rc != 0) {
        printk("sensor_sample_fetch() failed: %d\n", rc);
        return;
    }

    rc = sensor_channel_get(imu, SENSOR_CHAN_ACCEL_X, &accel[0]);
    rc |= sensor_channel_get(imu, SENSOR_CHAN_ACCEL_Y, &accel[1]);
    rc |= sensor_channel_get(imu, SENSOR_CHAN_ACCEL_Z, &accel[2]);

    rc |= sensor_channel_get(imu, SENSOR_CHAN_GYRO_X, &gyro[0]);
    rc |= sensor_channel_get(imu, SENSOR_CHAN_GYRO_Y, &gyro[1]);
    rc |= sensor_channel_get(imu, SENSOR_CHAN_GYRO_Z, &gyro[2]);

    sensor_channel_get(imu, SENSOR_CHAN_DIE_TEMP, &temp);

    if (rc < 0) {
        printk("Channel get failed: %d\n", rc);
        return;
    }

    printk("ACCEL: X=%d.%06d Y=%d.%06d Z=%d.%06d m/s²\n",
           accel[0].val1, accel[0].val2,
           accel[1].val1, accel[1].val2,
           accel[2].val1, accel[2].val2);
    printk("GYRO : X=%d.%06d Y=%d.%06d Z=%d.%06d dps\n",
           gyro[0].val1, gyro[0].val2,
           gyro[1].val1, gyro[1].val2,
           gyro[2].val1, gyro[2].val2);
    printk("TEMP : %d.%06d °C\n", temp.val1, temp.val2);
};

static struct nvs_fs fs;

static int nvs_initialize(void) {

    struct flash_pages_info info;
    int rc = 0;

	/* define the nvs file system by settings with:
	 *	sector_size equal to the pagesize,
	 *	3 sectors
	 *	starting at NVS_PARTITION_OFFSET
	 */
	fs.flash_device = NVS_PARTITION_DEVICE;
	if (!device_is_ready(fs.flash_device)) {
		printk("Flash device %s is not ready\n", fs.flash_device->name);
		return 0;
	}
	fs.offset = NVS_PARTITION_OFFSET;
	rc = flash_get_page_info_by_offs(fs.flash_device, fs.offset, &info);
	if (rc) {
		printk("Unable to get page info, rc=%d\n", rc);
		return 0;
	}
	fs.sector_size = info.size;
	fs.sector_count = 3U;

	rc = nvs_mount(&fs);
		if (rc) {
			printk("Flash Init failed, rc=%d\n", rc);
			return 0;
		}
    return rc;
}

void flash_store_data(uint8_t id, const void *data, size_t len) {
    int err = nvs_write(&fs, id, data, len);
    if (err < 0) {
        LOG_ERR("Failed to write: %d", err);
    } else {
        LOG_INF("Data stored at ID %d", id);
    }
}

void go_to_sleep(int ms) {
    LOG_INF("Sleeping for %d ms", ms);
    k_msleep(ms);  // Light sleep (thread sleep)
}

int main(void)
{
    LOG_INF("IMU Logger starting...");

        nvs_initialize();
        init_imu();

        while (1) {
            read_imu();
            int32_t dummy_data = 1234;
            flash_store_data(1, &dummy_data, sizeof(dummy_data));

            LOG_INF("Cycle complete, sleeping...");
            k_msleep(5000); // Sleep 5s
        }
}
