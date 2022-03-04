#!/usr/bin/env python

import sys
import heapq

def main () -> int:

    def getncs(r: int, c: int) -> set:
        return [i for i in [(r-1,c),(r+1,c),(r,c-1),(r,c+1)] \
            if i[0] >= 0 and i[0] <= lr and i[1] >= 0 and i[1] <= lc]

    itxt = open("input", mode='r').read().strip().splitlines()

    jq = [(int(v),i,j) for i, r in enumerate(itxt) for j, v in enumerate(r)]
    lr, lc = (max([r for (v,r,c) in jq]), max([c for (v,r,c) in jq])) #last

    jq = [(((r+c+v-1)%9+1),ir+(r*lr)+r,ic+(c*lc)+c) \
        for (v,ir,ic) in jq for c in range(5) for r in range(5)] #embiggen
    lr, lc = (max([r for (v,r,c) in jq]), max([c for (v,r,c) in jq])) #recalc last

    iq = {(r,c): int(v) for (v,r,c) in jq}
    oq = dict()

    jq.pop(0) # pop (0,0)
    cq = [(0,0,0)]
    heapq.heapify(cq)

    while len(jq) != len(oq.keys()):
        (v,r,c) = heapq.heappop(cq)

        for (nr, nc) in getncs(r,c):
            if v < iq.get((nr,nc)) or (r,c) not in oq.keys():
                heapq.heappush(cq,(iq.get((nr,nc))+v, nr,nc))

        oq.update({(r,c):v})

    oq.update({(r,c):v for (r,v,c) in cq if v < oq.get((r,c),99999999)})
    print(oq.get((lr,lc)))

if __name__ == '__main__':
    sys.exit(main())
