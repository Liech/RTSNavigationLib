class_name Formation extends Resource

@export var children : Array[Formation]
@export var name : String

@export var own_InterfacePoint : int 
@export var parent_interface_point : int     
@export var overwrite_width_with_interface_width : bool
@export var rotate_with_interface  : bool
@export var rotation : float
@export var category : String
@export var weight : float
@export var placement_behavior : RTSFormation.PlacementBehavior              



func randomize()->void:
	#randomize
	var prefix : String = ["Extensive ", "Mysterious ", "Edible ", "Fortified ", "Elongated ", "Tetra", "Un", "Inverse ","Main ", "Primary ", "El ", "Durable "].pick_random()
	var suffix : String = ["Squirrel", "Hawk", "Cheeta","Stoat", "Turtle", "Mare", "Fox", "Hound", "Hare", "Cat", "Elefant", "Toddler"].pick_random()
	name = prefix+suffix
	placement_behavior = [RTSFormation.PlacementBehavior.center_first_rts,RTSFormation.PlacementBehavior.distribute_evenly_rts,RTSFormation.PlacementBehavior.outer_first_rts].pick_random() 
	category = FormationEditor.categories.pick_random()
	rotate_with_interface = [false,true].pick_random()
	overwrite_width_with_interface_width = [false,true].pick_random()
	weight = randf()
	rotation = randf()*PI*2
	
