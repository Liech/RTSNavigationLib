class_name UnitType extends Resource

@export var color : Color
@export var name : String
@export var emoji : String
@export var category : String
@export_range(1,10) var size : int


func toRTS()->RTSBody:
	var result : RTSBody = RTSBody.new()
	result.size = size
	result.category = FormationEditor.unit_types.find(self)
	print(str(result.size) + " - " + str(result.category))
	return result
