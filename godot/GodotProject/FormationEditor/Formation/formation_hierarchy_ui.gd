extends Control

@onready var tree : Tree = $M/Sections/SectionTree

func _ready() -> void:
	FormationEditor.current_formation_changed.connect(current_formation_changed)
	FormationEditor.formations_changed.connect(current_formation_changed)
	current_formation_changed()
	
func current_formation_changed()->void:
	if (FormationEditor.current_formation == null):
		visible = false
		return
	visible = true
	if (!FormationEditor.formations.has(FormationEditor.current_formation)):
		return
	tree.clear()
	if (FormationEditor.formations.size() == 0):
		return;
	var selected := FormationEditor.current_formation
	add_tree_child(selected,null)
	
func add_tree_child(formation : Formation, parent : TreeItem)->void:
	var child : TreeItem
	if parent == null:
		child = tree.create_item()
	else:
		child = parent.create_child()
	child.set_text(0,formation.name)
	child.set_metadata(0,formation)
	for x in formation.children:
		add_tree_child(x,child)

func _on_select_pressed() -> void:
	var selection := tree.get_selected()
	if (selection):
		FormationEditor.current_formation = selection.get_metadata(0) as Formation
		FormationEditor.current_formation_changed.emit()
		
func _on_delete_pressed() -> void:
	var selection := tree.get_selected()
	if (selection and selection.get_parent()):
		var index :=selection.get_index()
		var parent := selection.get_parent().get_metadata(0) as Formation
		parent.children.remove_at(index)
		FormationEditor.formations_changed.emit()
		
func _on_add_pressed() -> void:
	var selection := tree.get_selected()
	if (selection):
		var new_formation : Formation = Formation.new()
		var prefix : String = ["North ", "West ", "East ", " South", "Back ", "Front ", "Side ", "False ", "True ", "Main ", "Sub "].pick_random()
		var suffix : String = ["Quarter", "Dangle", "Half", "Support", "Scout", "Defense", "Offense", "Lance", "Layer"].pick_random()
		new_formation.randomize()
		new_formation.name = prefix+suffix
		var selected := selection.get_metadata(0) as Formation
		selected.children.push_back(new_formation)
		FormationEditor.formations_changed.emit()
