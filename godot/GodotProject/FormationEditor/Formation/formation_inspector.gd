extends MarginContainer

@onready var tree : Tree = $Toolbox/Hierarchy/M/Sections/SectionTree

func _ready() -> void:
	FormationEditor.formations_changed.connect(formations_changed)
	formations_changed()
	pass

func formations_changed() -> void:	
	tree.clear()
	if (FormationEditor.formations.size() == 0):
		return;
	var selected := FormationEditor.formations[0]
	for x in selected.children:
		add_tree_child(x,null)
	
func add_tree_child(formation : Formation, parent : TreeItem)->void:
	var child : TreeItem
	if parent == null:
		child = tree.create_item()
	else:
		child = parent.create_child()
	child.set_text(0,formation.name)
	for x in formation.children:
		add_tree_child(x,child)
	pass
