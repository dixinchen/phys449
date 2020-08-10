#!/bin/bash
# start with Au = 99.99%, Al = 0.01%

make -j2
for ((i = 0 ; i <= 4 ; i++)); do
    ./NNSResponse -m shell0.mac -scorer 0
    ./NNSResponse -m shell0.mac -scorer 1
done

sed -i -e "s/el_Au, 99.99/el_Au, 99.95/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e 's/el_Al, 0.01/el_Al, 0.05/g' ~/Documents/passive_nns/src/DetectorConstruction.cc
make -j2
for ((i = 0 ; i <= 4 ; i++)); do
    ./NNSResponse -m shell0.mac -scorer 0
    ./NNSResponse -m shell0.mac -scorer 1
done

equ="="
dot="."
begin=s
end=/g
specialBeginAu=95/el_Au,\ 
specialBeginAl=05/el_Al,\ 
specialBeginAu2=05/el_Au,\ 
specialBeginAl2=95/el_Al,\ 
specialBeginAu3=00/el_Au,\ 
specialBeginAl3=00/el_Al,\ 
specialEndAu=90/g
specialEndAl=10/g
specialEndAu2=05/g
specialEndAl2=95/g
specialEndAu3=00/g
specialEndAl3=00/g

au=/el_Au,\ 
al=/el_Al,\ 

u=99
d=0
for ((i = 0 ; i <= 19 ; i++)); do
    aStr=$begin$au$u$dot$specialBeginAu$u$dot$specialEndAu
    sed -i -e "$aStr" ~/Documents/passive_nns/src/DetectorConstruction.cc   # 99.95 -> 99.90
    bStr=$begin$al$d$dot$specialBeginAl$d$dot$specialEndAl
    sed -i -e "$bStr" ~/Documents/passive_nns/src/DetectorConstruction.cc   # 0.05 -> 0.10
    make -j2
    for ((j = 0 ; j <= 4 ; j++)); do
        ./NNSResponse -m shell0.mac -scorer 0
        ./NNSResponse -m shell0.mac -scorer 1
    done
    echo "$aStr" >> density.txt
    echo "$bStr" >> density.txt

    h=90
    g=10 
    for ((j = 0 ; j <= 15 ; j++)); do
        str1=$begin$au$u$dot$h$au$u$dot
        h=$((h-5))
        str2=$str1$h$end
        sed -i -e "$str2" ~/Documents/passive_nns/src/DetectorConstruction.cc
        str3=$begin$al$d$dot$g$al$d$dot
        g=$((g+5))
        str4=$str3$g$end
        sed -i -e "$str4" ~/Documents/passive_nns/src/DetectorConstruction.cc 
        make -j2 
        for ((k = 0 ; k <= 4 ; k++)); do
            ./NNSResponse -m shell0.mac -scorer 0
            ./NNSResponse -m shell0.mac -scorer 1
        done
        echo "$str2" >> density.txt
        echo "$str4" >> density.txt
    done

    str1=$begin$au$u$dot$h$au$u$dot$specialEndAu2
    sed -i -e "$str1" ~/Documents/passive_nns/src/DetectorConstruction.cc   # 99.10 -> 99.05
    str2=$begin$al$d$dot$g$al$d$dot$specialEndAl2
    sed -i -e "$str2" ~/Documents/passive_nns/src/DetectorConstruction.cc   # 0.90 -> 0.95
    make -j2
    for ((j = 0 ; j <= 4 ; j++)); do
        ./NNSResponse -m shell0.mac -scorer 0
        ./NNSResponse -m shell0.mac -scorer 1
    done  
    echo "$str1" >> density.txt
    echo "$str2" >> density.txt

    str1=$begin$au$u$dot$specialBeginAu2$u$dot$specialEndAu3
    sed -i -e "$str1" ~/Documents/passive_nns/src/DetectorConstruction.cc   # 99.05 -> 99.00
    str21=$begin$al$d$dot$specialBeginAl2
    d=$((d+1))
    str22=$str21$d$dot$specialEndAl3
    sed -i -e "$str22" ~/Documents/passive_nns/src/DetectorConstruction.cc   # 0.95 -> 1.00
    make -j2
    for ((j = 0 ; j <= 4 ; j++)); do
        ./NNSResponse -m shell0.mac -scorer 0
        ./NNSResponse -m shell0.mac -scorer 1
    done
    echo "$str1" >> density.txt
    echo "$str22" >> density.txt

    str11=$begin$au$u$dot$specialBeginAu3
    u=$((u-1))
    str12=$str11$u$dot$specialEndAl2
    sed -i -e "$str12" ~/Documents/passive_nns/src/DetectorConstruction.cc   # 99.00 -> 98.95
    str2=$begin$al$d$dot$specialBeginAl3$d$dot$specialEndAu2
    sed -i -e "$str2" ~/Documents/passive_nns/src/DetectorConstruction.cc   # 1.00 -> 1.05
    make -j2
    for ((j = 0 ; j <= 4 ; j++)); do
        ./NNSResponse -m shell0.mac -scorer 0
        ./NNSResponse -m shell0.mac -scorer 1
    done
    echo "$str12" >> density.txt
    echo "$str2" >> density.txt
done