from json_serializer.Serializer import Serializer
from library.models import User
from library.models import Device

/* Constructor which list which class will be involved in 
*serialization/deserialization */
serializer = Serializer([
	User
	Device
])

