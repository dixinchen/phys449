# start with gold density = 13.3
equ="="
a=s/goldfoil_density
begin=$a$equ

dot="."
zero=3
b=/goldfoil_density
mid=$dot$zero$b$equ

g=/g
end=$dot$zero$g

density=13

for ((i = 0 ; i <=9 ; i++)); do
    str1=$begin$density$mid
    density=$((density+1))
    str2=$str1$density$end
    sed -i -e "$str2" ~/Documents/passive_nns/src/DetectorConstruction.cc
    make -j2
    for ((j = 0 ; j <= 4 ; j++)); do
        ./NNSResponse -m shell0.mac -scorer 0
        ./NNSResponse -m shell0.mac -scorer 1
    done
done

# sed -i -e "s/goldfoil_density=19.0/goldfoil_density=20.0/g" ~/Documents/passive_nns/src/DetectorConstruction.cc


# zero=0
# b=/goldfoil_density
# mid=$dot$zero$b$equ

# g=/g
# end=$dot$zero$g

# density=20

# for ((i = 0 ; i <=9 ; i++)); do
#     str1=$begin$density$mid
#     density=$((density+1))
#     str2=$str1$density$end
#     sed -i -e "$str2" ~/Documents/passive_nns/src/DetectorConstruction.cc
#     make -j2
#     for ((j = 0 ; j <= 4 ; j++)); do
#         ./NNSResponse -m shell0.mac -scorer 0
#         ./NNSResponse -m shell0.mac -scorer 1
#     done
# done

# sed -i -e "s/goldfoil_density=30.0/goldfoil_density=19.3/g" ~/Documents/passive_nns/src/DetectorConstruction.cc

open .