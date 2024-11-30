extends Node2D

var tickets : Array[int]

var placescene := preload("res://Place.tscn")
var unitscene := preload("res://Unit.tscn")

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	for i in range(50):
		var place := placescene.instantiate() as Node2D
		place.position = Vector2(randf_range(0,700),randf_range(0,700))
		$Places.add_child(place)
		var unit := unitscene.instantiate() as Node2D
		unit.position = Vector2(randf_range(0,700),randf_range(0,700))
		$Units.add_child(unit)

	var places : Array[Vector2];
	for b : Node2D in $Places.get_children():
		places.push_back(b.position);
	var units : Array[Vector2];
	for b : Node2D in $Units.get_children():
		units.push_back(b.position);
	
	tickets = RTSNavigation.usher(units,places)
	
func _process(_delta: float) -> void:
	queue_redraw()
	
func _draw()->void:
	for i in range(tickets.size()):
		var start :Vector2= $Units.get_child(i).position
		var end:Vector2=$Places.get_child(tickets[i]).position
		draw_line(start,end, Color.GREEN, 1.0)
