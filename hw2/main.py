X = "TCCCCGCTCTGCTCTGTCC--GGTCACA-GGA-CTTTTT-GC-CCTCTGTTCCCGGGTCCCT--CAGGCGGCCACCCAG-TGGGCA-CA-CTCC-CAGGCG---GCGCTCCG--"
Y = "A------T--G-T-TAACCAAGG--A-ATGGATCTGTGTCGTTCCAC-GTTCGAAGG-CCTTTTCTGATGAA-ATGAAGATAGGTTTCAACTCCACAGGTTATTGTGGTATGAT"

s = 0

for i in range(len(X)):
    if X[i] == "-" or Y[i] == "-":
        s += -2
    elif X[i] == Y[i]:
        s += 2
    else:
        s += -1

print(s)
