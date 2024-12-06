class_name statictest extends Node2D

var tickets : Array[int]

var placescene := preload("res://Place.tscn")
var unitscene := preload("res://Unit.tscn")

@export var formation : RTSFormation;

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	spread()
	
func spread()->void:
	for n in $Places.get_children():
		$Places.remove_child(n)
		n.queue_free()
	for n in $Units.get_children():
		$Units.remove_child(n)
		n.queue_free()
		
	var amount : int = 16
	var row :int = 4
	for i in range(amount):
		var place := placescene.instantiate() as Node2D
		place.position = Vector2((i%row) * 50,int(i/row) * 50) + Vector2(0,350)
		$Places.add_child(place)
		var unit := unitscene.instantiate() as Node2D
		unit.position = Vector2(randf_range(0,700),randf_range(0,700))
		$Units.add_child(unit)

	set_tickets()
	
func set_tickets()->void:
	var units : Array[RTSBody];
	var places : Array[RTSBody];
	for b : Node2D in $Places.get_children():
		var rts : RTSBody = RTSBody.new();
		rts.position = b.position;
		places.push_back(rts);
	for b : Node2D in $Units.get_children():
		var rts : RTSBody = RTSBody.new();
		rts.position = b.position;
		units.push_back(rts);
	tickets = RTSNavigation.usher(units,places)
	
func _process(_delta: float) -> void:
	queue_redraw()
	if (Input.is_action_just_pressed("ui_text_submit")):
		spread()
	if (Input.is_action_just_pressed("ui_text_delete")):
		set_tickets()
	
func _draw()->void:
	for i in range(tickets.size()):
		var start :Vector2= $Units.get_child(i).position
		var end:Vector2=$Places.get_child(tickets[i]).position
		draw_line(start,end, Color.GREEN, 1.0)
		$Units.get_child(i).set_target($Places.get_child(tickets[i]))
