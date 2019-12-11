from django.shortcuts import render
from django.http import HttpResponse
import os


# Create your views here.

def startTemp(request):
	if (request === 'POST'):
		os.system("python3 temp.py")

def ReceiveData(request):
	#data=json.load(request.)
