extends Node2D

func _ready() -> void:
	test_plugin_functionality()

func test_plugin_functionality()->void:
	var test:Splashscreen = Splashscreen.new();
	test.Screenshot()
	
	
	
	
	
