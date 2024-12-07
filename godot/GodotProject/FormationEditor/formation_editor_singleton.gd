class_name FormationEditorSingleton extends Node

signal categories_changed;
signal unit_types_changed;
signal formations_changed;
signal current_formation_changed;
signal unit_amount_changed;
signal formation_value_changed;

var categories : Array[String] 
var unit_types : Array[UnitType]
var formations : Array[Formation]

var unit_amount : Dictionary = {}
var current_root_formation : Formation = null
var current_formation : Formation = null
