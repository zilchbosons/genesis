#!/usr/bin/python
import mysql.connector

def getNearestRiemannPrime(cnx, cursor, nn):
    ele = int(nn)
    lb = 1
    f = open("python-out.txt", "w")
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
    print >>f, (mindeltalb, mindeltaub)
    f.close()

f=open("./out.txt","r")
content = f.readlines()

cnx = mysql.connector.connect(user='root', password='secret',
                              host='127.0.0.1',
                              database='intfact')
cursor = cnx.cursor()

for ele in content:
       nn = int(ele)
       gnn = getNearestRiemannPrime(cnx, cursor, nn)
       rnn = int(str(nn)[::-1]) 
       _gnn = getNearestRiemannPrime(cnx, cursor, rnn)

cursor.close()
cnx.close()
