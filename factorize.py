#!/usr/bin/python
import mysql.connector
import sys

def getNearestRiemannPrime(cnx, cursor, nn, f2, flag, fwd_pos, fwd_neg, bwd_pos, bwd_neg):
    ele = int(nn)
#   print(ele)
    lb = 1
    ub = ele + 60
    query = ("SELECT zero FROM zeros INNER JOIN primes WHERE prime=zero AND prime BETWEEN " + str(lb)+ " AND " + str(ub) + " AND zero BETWEEN " + str(lb) + " AND " + str(ub))
    cursor.execute(query)
    mindeltalb = sys.maxint
    minelelb = 0
    mindeltaub = sys.maxint
    mineleub = 0
    for (l) in cursor:
       nk = int(l[0])
       delta = nk - ele
#      print(delta)
       if (delta > 0) :
          delta = abs(delta) 
          if (delta < mindeltalb):
                mindeltalb = delta
                minelelb = nk
       else:
          delta = abs(delta) 
          if (delta < mindeltaub):
                mindeltaub = delta
                mineleub = nk
#   print >>f2, (minelelb, mineleub)
    if (flag == 1):
           fwd_neg.append(mindeltalb)
           fwd_pos.append(mindeltaub)
    else:
           bwd_neg.append(mindeltalb)
           bwd_pos.append(mindeltaub)

f=open("./out.txt","r")
f2 = open("python-out.txt", "w")
content = f.readlines()
cnx = mysql.connector.connect(user='root', password='secret',
                              host='192.168.1.1',
                              database='intfact')
cursor = cnx.cursor()
fwd_pos = []
fwd_neg = []
bwd_pos = []
bwd_neg = []
for ele in content:
       nn = int(ele)
       gnn = getNearestRiemannPrime(cnx, cursor, nn, f2, 1, fwd_pos, fwd_neg, bwd_pos, bwd_neg)
       rnn = int(str(nn)[::-1]) 
       _gnn = getNearestRiemannPrime(cnx, cursor, rnn, f2, 0, fwd_pos, fwd_neg, bwd_pos, bwd_neg)
#print("Lists:")
consolidated_list1 = []
consolidated_list2 = []
for el1, el2, el3, el4 in zip(fwd_pos, fwd_neg, bwd_pos[::-1], bwd_neg[::-1]):
     consolidated_list1.append([el1,el2])
     consolidated_list2.append([el3,el4])


print("Destruction")
for el1, el2 in zip(consolidated_list1, consolidated_list2):
     print(el1, "==>", el2)
     print("...")

print("Evolution")

for el3, el4 in zip(consolidated_list1[::-1], consolidated_list2[::-1]):
     print(el3, "==>", el4)
     print("...")

#    print(el1, el2)
#    print "==> "
#    print(el3, el4)
#    print "..."
 
cursor.close()
cnx.close()
f.close()
f2.close()
