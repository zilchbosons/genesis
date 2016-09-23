#!/usr/bin/python

from flask import Flask
from flask import request
from _factorize import _Factor
app = Flask(__name__)

#Temporary Begin
#def _Factor(args):
#   return str(args)

@app.route('/prime', methods= ['GET', 'POST'])
def factorize():
        if (request.method == 'POST'):
            return _Factor(str(request.form.get('num')))
        elif (request.method == 'GET'):
            return _Factor(str(request.args.get('num')))
        else:
            return None

@app.route('/factorize', methods= ['GET', 'POST'])
def factorize():
        if (request.method == 'POST'):
            return _Factor(str(request.form.get('num')))
        elif (request.method == 'GET'):
            return _Factor(str(request.args.get('num')))
        else:
            return None

if __name__ == '__main__':
   app.run(host="0.0.0.0", port="80")

