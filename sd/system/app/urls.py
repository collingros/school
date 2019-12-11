from django.conf.urls import url

import . from views

urlpatterns=[
	url(r'^ReceiveData/$',views.ReceiveData),
	url(r'^startTemp/$',views.startTemp),
]
