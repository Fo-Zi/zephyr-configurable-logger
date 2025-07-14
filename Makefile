# Shortcuts focused solely on host‑based tests (native_sim)

.PHONY: unit_tests clean_unit_tests

unit_tests:
	west twister -W -T app/tests -p native_sim --outdir twister-out --clobber-output -v

clean_unit_tests:
	rm -rf twister-out*
