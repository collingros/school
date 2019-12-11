from django.db import models

# Create your models here.

class User (models.Model):
	
	first_name = models.CharField(max_length=30)
	last_name = models.CharField(max_length=30)
	user_name = models.CharField(max_length=30)
	password = models.CharField(max_length=30)

	class Meta:
		abstract = True

	def as_json(self):
		return dict(
			first_name = self.first_name
			last_name = self.last_name
			user_name = self.user_name
			password = self.password)

class Devices (models.Model)

	device_name = models.CharField(max_length=30)
	model_number = models.CharField(max_length=30)
	id_number = models.IntegerField(max_length=4)
	
	class Meta:
		abstract = True

	def __self__(self):
		device_name = self.device_name
		model_number = self.model_number
		id_number = self.id_number
