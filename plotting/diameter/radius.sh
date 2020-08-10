# start with gold_rad=0.8, radius=0.801 (in shell0.mac)
# radius of the gold foil changes from 0.50 to 0.95 with 0.05 increment
# radius of the source changes from 0.501 to 0.951 with 0.05 increment

sed -i -e "s/gold_rad=0.8/gold_rad=0.10/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/radius 0.801/radius 0.101/g" ~/Documents/passive_nns/build/shell0.mac
make -j2
for ((i = 0 ; i <= 4 ; i++)); do
    ./NNSResponse -m shell0.mac -scorer 0
    ./NNSResponse -m shell0.mac -scorer 1
done
# echo 0.10

equ="="
zero=0
dot="."
s=s
gd=/gold_rad
g=/g
rd=/radius\ 
one=1

begin=$s$gd$equ$zero$dot
srcbegin=$s$rd$zero$dot

radius=10

for ((i = 0 ; i <= 15 ; i++)); do
    mid=$begin$radius$gd$equ$zero$dot
    srcmid=$srcbegin$radius$one$rd$zero$dot
    radius=$((radius+5))
    fin=$mid$radius$g
    srcfin=$srcmid$radius$one$g
    sed -i -e "$fin" ~/Documents/passive_nns/src/DetectorConstruction.cc
    sed -i -e "$srcfin" ~/Documents/passive_nns/build/shell0.mac
    make -j2
    for ((j = 0 ; j <= 4 ; j++)); do
        ./NNSResponse -m shell0.mac -scorer 0
        ./NNSResponse -m shell0.mac -scorer 1
    done
    # echo "$radius"
done

sed -i -e "s/gold_rad=0.90/gold_rad=0.8/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/radius 0.901/radius 0.801/g" ~/Documents/passive_nns/build/shell0.mac

open .
echo -en "\007"