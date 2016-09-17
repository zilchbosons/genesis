#!/usr/bin/python
import mysql.connector

def getNearestRiemannPrime(cnx, cursor, nn):
    ele = int(nn)
    lb = 1
    if (ele  > 50 ):
       lb = ele - 50
    ub = ele + 50
    query = ("SELECT zero FROM zeros INNER JOIN primes WHERE prime=zero AND prime BETWEEN " + str(lb)+ " AND " + str(ub) + " AND zero BETWEEN " + str(lb) + " AND " + str(ub))
    cursor.execute(query)
    for (l)in cursor:
       print(l[0])

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
