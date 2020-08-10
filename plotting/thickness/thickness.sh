#!/bin/bash
# start with thickness = 0.0050, length = 2.5450
# equ="="
# s=s
# g=/g
# g4ck=/G4double\ gold_thick
# g4rt=/G4double\ small_insert_len
# zero=0
# two=2
# dot="."

# au=50
# pl=5450

# for ((i = 0 ; i <= 8 ; i++)); do
#     gold1=$s$g4ck$equ$zero$dot$zero$zero$au$g4ck$equ$zero$dot$zero$zero
#     au=$((au+5))
#     gold2=$gold1$au$g
#     sed -i -e "$gold2" ~/Documents/passive_nns/src/DetectorConstruction.cc
#     ins1=$s$g4rt$equ$two$dot$pl$g4rt$equ$two$dot
#     pl=$((pl-5))
#     ins2=$ins1$pl$g
#     sed -i -e "$ins2" ~/Documents/passive_nns/src/DetectorConstruction.cc
#     make -j2 
#     for ((j = 0 ; j <= 4 ; j++)); do
#         ./NNSResponse -m shell0.mac -scorer 0
#         ./NNSResponse -m shell0.mac -scorer 1
#     done
# done

# sed -i -e "s/G4double gold_thick=0.0095/G4double gold_thick=0.0100/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e 's/G4double small_insert_len=2.5405/G4double small_insert_len=2.5400/g' ~/Documents/passive_nns/src/DetectorConstruction.cc
# make -j2
# for ((i = 0 ; i <= 4 ; i++)); do
#     ./NNSResponse -m shell0.mac -scorer 0
#     ./NNSResponse -m shell0.mac -scorer 1
# done

# au=100
# pl=5400
# for ((i = 0 ; i <= 9 ; i++)); do
#     gold1=$s$g4ck$equ$zero$dot$zero$au$g4ck$equ$zero$dot$zero
#     au=$((au+5))
#     gold2=$gold1$au$g
#     sed -i -e "$gold2" ~/Documents/passive_nns/src/DetectorConstruction.cc
#     ins1=$s$g4rt$equ$two$dot$pl$g4rt$equ$two$dot
#     pl=$((pl-5))
#     ins2=$ins1$pl$g
#     sed -i -e "$ins2" ~/Documents/passive_nns/src/DetectorConstruction.cc
#     make -j2 
#     for ((j = 0 ; j <= 4 ; j++)); do
#         ./NNSResponse -m shell0.mac -scorer 0
#         ./NNSResponse -m shell0.mac -scorer 1
#     done
# done

############################################################

# # start with thickness = 0.005, length = 2.545
# make -j2
# for ((i = 0 ; i <= 4 ; i++)); do
#     ./NNSResponse -m shell0.mac -scorer 0
#     ./NNSResponse -m shell0.mac -scorer 1
# done

# equ="="
# str1=s/G4double\ gold_thick\ $equ\ 0.00
# str2=/G4double\ gold_thick\ $equ\ 0.00
# str3=/g
# h=5
# sstr1=s/G4double\ small_insert_len\ $equ\ 2.54
# sstr2=/G4double\ small_insert_len\ $equ\ 2.54
# g=5
# for ((i = 0 ; i <= 3 ; i++)); do
#     str4=$str1$h$str2
#     h=$((h+1))
#     str5=$str4$h$str3
#     sed -i -e "$str5" ~/Documents/passive_nns/src/DetectorConstruction.cc
#     a=$sstr1$g$sstr2
#     g=$((g-1))
#     b=$a$g$str3
#     sed -i -e "$b" ~/Documents/passive_nns/src/DetectorConstruction.cc 
#     make -j2 
#     for ((j = 0 ; j <= 4 ; j++)); do
#         ./NNSResponse -m shell0.mac -scorer 0
#         ./NNSResponse -m shell0.mac -scorer 1
#     done
# done

# sed -i -e "s/G4double gold_thick = 0.009/G4double gold_thick = 0.010/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e 's/G4double small_insert_len = 2.541/G4double small_insert_len = 2.540/g' ~/Documents/passive_nns/src/DetectorConstruction.cc
# make -j2
# for ((i = 0 ; i <= 4 ; i++)); do
#     ./NNSResponse -m shell0.mac -scorer 0
#     ./NNSResponse -m shell0.mac -scorer 1
# done

# equ="="
# str1=s/G4double\ gold_thick\ $equ\ 0.01
# str2=/G4double\ gold_thick\ $equ\ 0.01
# str3=/g
# h=0
# sstr1=s/G4double\ small_insert_len\ $equ\ 2.5
# sstr2=/G4double\ small_insert_len\ $equ\ 2.5
# g=40
# for ((i = 0 ; i <= 4 ; i++)); do
#     str4=$str1$h$str2
#     h=$((h+1))
#     str5=$str4$h$str3
#     sed -i -e "$str5" ~/Documents/passive_nns/src/DetectorConstruction.cc
#     a=$sstr1$g$sstr2
#     g=$((g-1))
#     b=$a$g$str3
#     sed -i -e "$b" ~/Documents/passive_nns/src/DetectorConstruction.cc 
#     make -j2 
#     for ((j = 0 ; j <= 4 ; j++)); do
#         ./NNSResponse -m shell0.mac -scorer 0
#         ./NNSResponse -m shell0.mac -scorer 1
#     done
# done

############################################################

sed -i -e "s/gold_thick=0.01/gold_thick=0.005/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/275/27375/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/small_insert_len=2.54/small_insert_len=2.5425/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/,0.005/,0.0025/g" ~/Documents/passive_nns/src/ImportanceDetectorConstruction.cc
sed -i -e "s/0.00501/0.00251/g" ~/Documents/passive_nns/build/shell0.mac
make -j2
for ((i = 0 ; i <= 4 ; i++)); do
    ./NNSResponse -m shell0.mac -scorer 0
    ./NNSResponse -m shell0.mac -scorer 1
done
# ./NNSResponse -m shell0.mac -scorer 0
# ./NNSResponse -m shell0.mac -scorer 1

sed -i -e "s/gold_thick=0.005/gold_thick=0.010/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/27375/27500/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/small_insert_len=2.5425/small_insert_len=2.5400/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/,0.0025/,0.0050/g" ~/Documents/passive_nns/src/ImportanceDetectorConstruction.cc
sed -i -e "s/0.00251/0.00501/g" ~/Documents/passive_nns/build/shell0.mac
make -j2
for ((i = 0 ; i <= 4 ; i++)); do
    ./NNSResponse -m shell0.mac -scorer 0
    ./NNSResponse -m shell0.mac -scorer 1
done
# ./NNSResponse -m shell0.mac -scorer 0
# ./NNSResponse -m shell0.mac -scorer 1

sed -i -e "s/gold_thick=0.010/gold_thick=0.015/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/27500/27625/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/small_insert_len=2.5400/small_insert_len=2.5375/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/,0.0050/,0.0075/g" ~/Documents/passive_nns/src/ImportanceDetectorConstruction.cc
sed -i -e "s/0.00501/0.00751/g" ~/Documents/passive_nns/build/shell0.mac
make -j2
for ((i = 0 ; i <= 4 ; i++)); do
    ./NNSResponse -m shell0.mac -scorer 0
    ./NNSResponse -m shell0.mac -scorer 1
done
# ./NNSResponse -m shell0.mac -scorer 0
# ./NNSResponse -m shell0.mac -scorer 1

sed -i -e "s/gold_thick=0.015/gold_thick=0.020/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/27625/27750/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/small_insert_len=2.5375/small_insert_len=2.5350/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/,0.0075/,0.0100/g" ~/Documents/passive_nns/src/ImportanceDetectorConstruction.cc
sed -i -e "s/0.00751/0.01001/g" ~/Documents/passive_nns/build/shell0.mac
make -j2
for ((i = 0 ; i <= 4 ; i++)); do
    ./NNSResponse -m shell0.mac -scorer 0
    ./NNSResponse -m shell0.mac -scorer 1
done
# ./NNSResponse -m shell0.mac -scorer 0
# ./NNSResponse -m shell0.mac -scorer 1

# sed -i -e "s/gold_thick=0.020/gold_thick=0.025/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e "s/27750/27875/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e "s/small_insert_len=2.5350/small_insert_len=2.5325/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e "s/,0.0100/,0.0125/g" ~/Documents/passive_nns/src/ImportanceDetectorConstruction.cc
# sed -i -e "s/0.01001/0.01251/g" ~/Documents/passive_nns/build/shell0.mac
# make -j2
# # for ((i = 0 ; i <= 4 ; i++)); do
# #     ./NNSResponse -m shell0.mac -scorer 0
# #     ./NNSResponse -m shell0.mac -scorer 1
# # done
# ./NNSResponse -m shell0.mac -scorer 0
# ./NNSResponse -m shell0.mac -scorer 1

# sed -i -e "s/gold_thick=0.025/gold_thick=0.030/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e "s/27875/28000/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e "s/small_insert_len=2.5325/small_insert_len=2.5300/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e "s/,0.0125/,0.0150/g" ~/Documents/passive_nns/src/ImportanceDetectorConstruction.cc
# sed -i -e "s/0.01251/0.01501/g" ~/Documents/passive_nns/build/shell0.mac
# make -j2
# # for ((i = 0 ; i <= 4 ; i++)); do
# #     ./NNSResponse -m shell0.mac -scorer 0
# #     ./NNSResponse -m shell0.mac -scorer 1
# # done
# ./NNSResponse -m shell0.mac -scorer 0
# ./NNSResponse -m shell0.mac -scorer 1

sed -i -e "s/gold_thick=0.020/gold_thick=0.01/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/27750/275/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/small_insert_len=2.5350/small_insert_len=2.54/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/,0.0100/,0.005/g" ~/Documents/passive_nns/src/ImportanceDetectorConstruction.cc
sed -i -e "s/0.01251/0.00501/g" ~/Documents/passive_nns/build/shell0.mac

sed -i -e "s/gold_thick=0.01/gold_thick=0.0025/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/275/273125/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/small_insert_len=2.54/small_insert_len=2.54375/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/,0.005/,0.00125/g" ~/Documents/passive_nns/src/ImportanceDetectorConstruction.cc
sed -i -e "s/0.00501/0.00126/g" ~/Documents/passive_nns/build/shell0.mac
make -j2
for ((i = 0 ; i <= 4 ; i++)); do
    ./NNSResponse -m shell0.mac -scorer 0
    ./NNSResponse -m shell0.mac -scorer 1
done
# ./NNSResponse -m shell0.mac -scorer 0
# ./NNSResponse -m shell0.mac -scorer 1

sed -i -e "s/gold_thick=0.0025/gold_thick=0.0075/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/273125/274375/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/small_insert_len=2.54375/small_insert_len=2.54125/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/,0.00125/,0.00375/g" ~/Documents/passive_nns/src/ImportanceDetectorConstruction.cc
sed -i -e "s/0.00126/0.00376/g" ~/Documents/passive_nns/build/shell0.mac
make -j2
for ((i = 0 ; i <= 4 ; i++)); do
    ./NNSResponse -m shell0.mac -scorer 0
    ./NNSResponse -m shell0.mac -scorer 1
done
# ./NNSResponse -m shell0.mac -scorer 0
# ./NNSResponse -m shell0.mac -scorer 1

sed -i -e "s/gold_thick=0.0075/gold_thick=0.0125/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/274375/275625/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/small_insert_len=2.54125/small_insert_len=2.53875/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/,0.00375/,0.00625/g" ~/Documents/passive_nns/src/ImportanceDetectorConstruction.cc
sed -i -e "s/0.00376/0.00626/g" ~/Documents/passive_nns/build/shell0.mac
make -j2
for ((i = 0 ; i <= 4 ; i++)); do
    ./NNSResponse -m shell0.mac -scorer 0
    ./NNSResponse -m shell0.mac -scorer 1
done
# ./NNSResponse -m shell0.mac -scorer 0
# ./NNSResponse -m shell0.mac -scorer 1

sed -i -e "s/gold_thick=0.0125/gold_thick=0.0175/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/275625/276875/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/small_insert_len=2.53875/small_insert_len=2.53625/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/,0.00625/,0.00875/g" ~/Documents/passive_nns/src/ImportanceDetectorConstruction.cc
sed -i -e "s/0.00626/0.00876/g" ~/Documents/passive_nns/build/shell0.mac
make -j2
for ((i = 0 ; i <= 4 ; i++)); do
    ./NNSResponse -m shell0.mac -scorer 0
    ./NNSResponse -m shell0.mac -scorer 1
done
# ./NNSResponse -m shell0.mac -scorer 0
# ./NNSResponse -m shell0.mac -scorer 1

# sed -i -e "s/gold_thick=0.0175/gold_thick=0.0225/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e "s/276875/278125/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e "s/small_insert_len=2.53625/small_insert_len=2.53375/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e "s/,0.00875/,0.01125/g" ~/Documents/passive_nns/src/ImportanceDetectorConstruction.cc
# sed -i -e "s/0.00876/0.01126/g" ~/Documents/passive_nns/build/shell0.mac
# make -j2
# for ((i = 0 ; i <= 1 ; i++)); do
#     ./NNSResponse -m shell0.mac -scorer 0
#     ./NNSResponse -m shell0.mac -scorer 1
# done
# ./NNSResponse -m shell0.mac -scorer 0
# ./NNSResponse -m shell0.mac -scorer 1

# sed -i -e "s/gold_thick=0.0225/gold_thick=0.0275/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e "s/278125/279375/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e "s/small_insert_len=2.53375/small_insert_len=2.53125/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e "s/,0.01125/,0.01375/g" ~/Documents/passive_nns/src/ImportanceDetectorConstruction.cc
# sed -i -e "s/0.01126/0.01376/g" ~/Documents/passive_nns/build/shell0.mac
# make -j2
# for ((i = 0 ; i <= 1 ; i++)); do
#     ./NNSResponse -m shell0.mac -scorer 0
#     ./NNSResponse -m shell0.mac -scorer 1
# done
# ./NNSResponse -m shell0.mac -scorer 0
# ./NNSResponse -m shell0.mac -scorer 1

# sed -i -e "s/gold_thick=0.0275/gold_thick=0.01/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e "s/279375/275/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e "s/small_insert_len=2.53125/small_insert_len=2.54/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e "s/,0.01375/,0.005/g" ~/Documents/passive_nns/src/ImportanceDetectorConstruction.cc
# sed -i -e "s/0.01376/0.00501/g" ~/Documents/passive_nns/build/shell0.mac

sed -i -e "s/gold_thick=0.0175/gold_thick=0.01/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/276875/275/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/small_insert_len=2.53625/small_insert_len=2.54/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
sed -i -e "s/,0.00875/,0.005/g" ~/Documents/passive_nns/src/ImportanceDetectorConstruction.cc
sed -i -e "s/0.00876/0.00501/g" ~/Documents/passive_nns/build/shell0.mac

open .

echo -en "\007"
echo -en "\007"
echo -en "\007"

# s=s
# g=/g
# dot="."
# comma=","
# equ="="
# zero=0
# one=1
# two=2

# small=/small_insert_len
# gold=/gold_thick

# length=5400
# thick=10
# imp=50

# b1=$s$small$equ$two$dot$length$small$equ$two$dot
# b2=$s$gold$equ$zero$dot$zero$thick$gold$equ$zero$dot$zero
# b3=$s$comma$zero$dot$zero$zero

# length=$((length+25))
# thick=$((thick+5))
# e1=$b1$length$g
# e2=$b2$thick$g