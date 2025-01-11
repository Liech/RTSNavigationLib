class_name PreviewScene extends Node2D

var unit_scene := preload("res://FormationEditor/Formation/preview_unit.tscn")

@onready var camera : Camera2D = $Camera2D
@onready var units : Node2D = $Units
@onready var interface_points := $FormationInterface

var start_position : Vector2;
var start_zoom : Vector2;

var result_shapes : Array[PackedVector2Array];
var debug_shapes : Array[PackedVector2Array];

func _ready() -> void:
	FormationEditor.current_formation_changed.connect(formation_changed)
	FormationEditor.formation_value_changed.connect(formation_changed)
	FormationEditor.unit_amount_changed.connect(formation_changed)
	FormationEditor.preview_scene = self
	start_position= camera.offset
	start_zoom = camera.zoom
	formation_changed()

func reset_camera() -> void:
	camera.offset = start_position
	camera.zoom = start_zoom
	
func formation_changed() -> void:
	if(!FormationEditor.current_root_formation):
		return
	var formation := FormationEditor.current_root_formation.toRTS()
	var bodies : Array[RTSBody]
	
	var counter : int = 0;
	for x in FormationEditor.unit_types:
		print(x.name)
		if !FormationEditor.unit_amount.has(x.name):
			counter += 1
			continue
		var amount : int = FormationEditor.unit_amount[x.name]
		var body : RTSBody = x.toRTS() 
		body.category = counter;
		for i in range(amount):
			bodies.push_back(body.duplicate())
		counter += 1
	print(formation.toJson())
	var result := formation.calculate(bodies)
	FormationEditor.formation_shapes = formation.get_result_shapes()
	debug_shapes = formation.get_debug_shapes()
	for n in units.get_children():
		units.remove_child(n)
		n.queue_free()
		
	for x in result:
		var pos := x.position
		var unit := unit_scene.instantiate() as FormationPreviewUnit
		unit.type = FormationEditor.unit_types[x.category]
		unit.position = pos * FormationEditor.scale_factor
		units.add_child(unit)
	interface_points.formation_changed()
