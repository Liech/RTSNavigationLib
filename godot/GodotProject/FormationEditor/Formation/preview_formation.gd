class_name PreviewScene extends Node2D

var unit_scene := preload("res://FormationEditor/Formation/preview_unit.tscn")

@onready var camera : Camera2D = $Camera2D
@onready var units : Node2D = $Units

@export var scale_factor : float = 30

var start_position : Vector2;
var start_zoom : Vector2;

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
	
	for x in FormationEditor.unit_types:
		if !FormationEditor.unit_amount.has(x.name):
			continue
		var amount : int = FormationEditor.unit_amount[x.name]
		var body : RTSBody = x.toRTS() 
		for i in range(amount):
			bodies.push_back(body.duplicate())
	if (bodies.size() == 1):
		return
	print(formation.toJson())
	var result := formation.calculate(bodies)
	
	for n in units.get_children():
		units.remove_child(n)
		n.queue_free()
		
	for x in result:
		var pos := x.position
		var unit := unit_scene.instantiate() as FormationPreviewUnit
		unit.type = FormationEditor.unit_types[0]
		unit.position = pos * scale_factor
		units.add_child(unit)
