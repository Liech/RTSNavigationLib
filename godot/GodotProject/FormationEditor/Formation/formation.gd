class_name Formation extends Resource

enum Shape{Rectangle,Triangle,Circle}

@export var children : Array[Formation]
@export var name : String

@export var own_InterfacePoint : int 
@export var parent_interface_point : int     
@export var overwrite_width_with_interface_width : bool
@export var rotate_with_interface  : bool
@export var rotation : float
@export var category : Array[String]
@export var weight : float
@export var placement_behavior : RTSFormation.PlacementBehavior       
@export var cut_behavior : RTSFormation.PlacementBehavior       
@export var shape : Shape      
@export var hollow : float
@export var size : Vector2
@export var scaling_behavior : RTSFormationShape.ScalingBehavior
@export var arc : float       
@export var center_shift : bool
@export var reamining_unit_sink : bool

func randomize()->void:
	#randomize
	var prefix : String = ["Extensive ", "Mysterious ", "Edible ", "Fortified ", "Elongated ", "Tetra", "Un", "Inverse ","Main ", "Primary ", "El ", "Durable "].pick_random()
	var suffix : String = ["Squirrel", "Hawk", "Cheeta","Stoat", "Turtle", "Mare", "Fox", "Hound", "Hare", "Cat", "Elefant", "Toddler"].pick_random()
	name = prefix+suffix
	placement_behavior = [RTSFormation.PlacementBehavior.center_first_rts,RTSFormation.PlacementBehavior.distribute_evenly_rts,RTSFormation.PlacementBehavior.outer_first_rts].pick_random() 
	cut_behavior = [RTSFormation.PlacementBehavior.center_first_rts,RTSFormation.PlacementBehavior.distribute_evenly_rts,RTSFormation.PlacementBehavior.outer_first_rts].pick_random() 
	category = [FormationEditor.categories.pick_random()]
	rotate_with_interface = [false,true].pick_random()
	overwrite_width_with_interface_width = [false,true].pick_random()
	weight = randf()
	rotation = randf()*PI*2
	arc = randf()*PI*2
	shape = [Shape.Rectangle,Shape.Triangle,Shape.Circle].pick_random()
	@warning_ignore("int_as_enum_without_cast")
	scaling_behavior = 2
	hollow = 0
	center_shift = [false,true].pick_random()
	reamining_unit_sink= false;
	size = Vector2(1,1)
	
func toRTS() -> RTSFormation:
	var result : RTSFormation = RTSFormation.new()
	
	result.categories.clear()
	var counter : int = 0
	for x in FormationEditor.unit_types:
		print(x.category)
		if (category.has(x.category)):
			result.categories.push_back(counter)
		counter += 1
	
	print(result.categories)
	result.own_interface_point = own_InterfacePoint
	result.parent_interface_point = parent_interface_point
	result.overwrite_width_with_interface_width = overwrite_width_with_interface_width
	result.rotate_with_interface = rotate_with_interface
	result.rotation = rotation
	result.weight = weight
	result.placement_behavior = placement_behavior
	result.center_shift = center_shift
	result.remaining_unit_sink = reamining_unit_sink;
	result.cut_behavior = cut_behavior;
	
	if (shape == Shape.Rectangle):
		result.shape =RTSShapeRect.new()
	elif (shape == Shape.Triangle):
		result.shape =RTSShapeTri.new()
	elif (shape == Shape.Circle):
		result.shape =RTSShapeArc.new()
		result.shape.arc_angle_radian = arc
	
	result.shape.hollow = 1-hollow
	result.shape.base_size = size
	result.shape.scaling_behavior = scaling_behavior
		
	for x in children:
		result.children.push_back(x.toRTS())
	return result
