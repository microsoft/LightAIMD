bin/lightaimd --hf --spf --silent --check-results 1
echo ""
bin/lightaimd --dft --spf --xc-functional 1,7 --silent --check-results 2
echo ""
bin/lightaimd --dft --spf --xc-functional 101,130 --silent --check-results 3
echo ""
bin/lightaimd --dft --spf --xc-functional 402 --silent --check-results 4
echo ""
bin/lightaimd --dft --spf --xc-functional 203,233 --silent --check-results 5
echo ""
bin/lightaimd --dft --spf --xc-functional 450,236 --silent --check-results 6
