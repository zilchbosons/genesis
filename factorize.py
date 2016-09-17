#!/usr/bin/python
import mysql.connector

def getNearestRiemannPrime(cnx, cursor, nn, f2):
    ele = int(nn)
    lb = 1
    if (ele  > 50 ):
       lb = ele - 50
    ub = ele + 50
    query = ("SELECT zero FROM zeros INNER JOIN primes WHERE prime=zero AND prime BETWEEN " + str(lb)+ " AND " + str(ub) + " AND zero BETWEEN " + str(lb) + " AND " + str(ub))
    cursor.execute(query)
    mindeltalb = ele
    minelelb = 0
    mindeltaub = ele
    mineleub = 0
    for (l) in cursor:
       nk = int(l[0])
       delta = nk - nn
       if (delta > 0):
          delta = abs(delta) 
          if (delta < mindeltalb):
                mindeltalb = -delta
                minelelb = nk
       else:
          delta = abs(delta) 
          if (delta < mindeltaub):
                mindeltaub = delta
                mineleub = nk
    print >>f2, (mindeltalb, mindeltaub)

f=open("./out.txt","r")
f2 = open("python-out.txt", "w")
content = f.readlines()

cnx = mysql.connector.connect(user='root', password='secret',
                              host='127.0.0.1',
                              database='intfact')
cursor = cnx.cursor()

for ele in content:
       nn = int(ele)
       gnn = getNearestRiemannPrime(cnx, cursor, nn, f2)
       rnn = int(str(nn)[::-1]) 
       _gnn = getNearestRiemannPrime(cnx, cursor, rnn, f2)

cursor.close()
cnx.close()
f.close()
f2.close()
