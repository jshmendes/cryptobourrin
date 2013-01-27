#!/bin/sh

echo "################### Building binary ################\n" ;
gcc -o wiener wiener.c -lgmp ;

echo "################### Beginning of Test ################\n" ;
./wiener dec 25411171 27962863 ;
echo "\n#######################################\n" ;
./wiener dec 60728973 160523347 ;
echo "\n#######################################\n" ;
./wiener dec 1908717316858446782674807627631 2746482122383906972393557363644983749146398460239422282612197 ;
echo "\n#######################################\n" ;
./wiener dec 3594320245477 7978886869909 ;
echo "\n#######################################\n" ;
./wiener hex 802EF8CC586F35606E6B1B04FEF635D50DE2EABE9507ADA29662517F60517821E3C764AF09C2D7CD9DF0467250F83437443EA2BEA2BC719333351F280CE9E4F9 C836AC35487C4DF89786C40E6F708777679DCC8D3AA3E1D33AC420D5B30531E478E6FD137B26D5AAF22A0701561281AC010DC3CFBFCFD5573CCA5FFAB2BFD4CF ;
echo "\n#######################################\n" ;
./wiener dec 921318991 7978886869909 ;
echo "\n#######################################\n" ;
./wiener dec 4603830998027 7978886869909 ;
echo "\n#######################################\n" ;
./wiener dec 263 7978886869909 ;
echo "\n#######################################\n" ;
./wiener dec 6055258312152372605476785266317750951108834153931 8133876630876764379064472085871019680113623317877
echo "################### End of Test ####################\n" ;