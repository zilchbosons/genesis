#!/usr/bin/python

from flask import Flask
from flask import request
app = Flask(__name__)

#Temporary Begin
def _Factor(args):
   return str(args)

@app.route('/factorize', methods= ['GET', 'POST'])
def factorize():
        if (request.method == 'POST'):
            return _Factor(request.form)
        elif (request.method == 'GET'):
            return _Factor(request.args)
        else:
            return None

if __name__ == '__main__':
   app.run(host="0.0.0.0", port="80")

