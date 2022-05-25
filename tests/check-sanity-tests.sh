bash tests/compare-with-ref-energies-forces.sh > /tmp/compare-with-ref-energies-forces.log
if [[ $(grep Failed /tmp/compare-with-ref-energies-forces.log) ]]; then echo "Failed" && exit 1; else echo "Passed" && exit 0; fi
