extends Node2D

var button_scene := preload("res://FormationEditor/Formation/interface_point.tscn")

var current_index := 0
var parent_index := 0


func formation_changed() -> void:
	update_indices()
	update_buttons()
	queue_redraw()
	pass

func update_indices() -> void:
	var root := FormationEditor.current_root_formation
	var current := FormationEditor.current_formation
	
	update_indices_recurse(-1,0,root,current, 0)
	
	pass
	
func update_buttons()->void:
	for n in get_children():
		remove_child(n)
		n.queue_free()
	
	if (FormationEditor.formation_shapes.size() <= current_index):
		return
	for i in range(FormationEditor.formation_shapes[current_index].size()):
		var pos := FormationEditor.formation_shapes[current_index][i]
		var button := button_scene.instantiate() as interface_point
		button.position = pos * FormationEditor.scale_factor - button.size/2
		add_child(button)
	
	pass
	
func update_indices_recurse(parent_i : int, current_i : int,current : Formation, target : Formation, counter : int) -> int:
	if (current == target):
		current_index = current_i
		parent_index = parent_i
	else:
		for child in current.children:
			counter += 1
			counter = update_indices_recurse(current_i, counter, child,target,counter)
	
	return counter
	
func _draw() -> void:
	var count := 0
	for poly in FormationEditor.formation_shapes:
		if (poly.size()<2):
			continue;
		var clr := Color.WHITE
		if (count == parent_index):
			clr = Color.CYAN
		if (count == current_index):
			clr = Color.RED
		for i in range(1,len(poly)):
			draw_line(poly[i-1]*FormationEditor.scale_factor,poly[i]*FormationEditor.scale_factor,clr);
		draw_line(poly[len(poly)-1]*FormationEditor.scale_factor,poly[0]*FormationEditor.scale_factor,clr);
		count += 1
	
