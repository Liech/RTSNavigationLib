class_name FormationEditorSingleton extends Node

@warning_ignore("unused_signal")
signal categories_changed;
@warning_ignore("unused_signal")
signal unit_types_changed;
@warning_ignore("unused_signal")
signal formations_changed;
@warning_ignore("unused_signal")
signal current_formation_changed;
@warning_ignore("unused_signal")
signal unit_amount_changed;
@warning_ignore("unused_signal")
signal formation_value_changed;

var categories : Array[String] 
var unit_types : Array[UnitType]
var formations : Array[Formation]

var unit_amount : Dictionary = {}
var current_root_formation : Formation = null
var current_formation : Formation = null
var preview_scene : PreviewScene = null
