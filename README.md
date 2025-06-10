# safe-zone
This Project is created due to completing my final project in advanced programming course with Reza Fuad Rachmadi, S.T.,M.T.,Ph.D as a lecture.

this also can be a template for pllatformer game project.

# Features
in this project there is a tools for character and scene builder to prevent repetitve behaviour.

- ## Animation
    this is a tools to play animation per frame, it will rechieve directory of the sprite, animation name, sprite, frame_rate, and resize, then it will update the sprite texture everytime you call animate() mthod.

- ## Scene
    this is a tools to create scene that need paralax background. each scene in this workspace are controlling all the event inside. this class  has a gravity method if you want to aply it on some sprite 


- ## State
    this is a tool to creating a state inside a scene. this class has handleEvent method, update method, render method, and next state method which is required for the game to run. (will explain the code flow later)

# Workspace
- ##  Assets
    like it's name, this is a folder that contain all the necessary sprite sheet or background.
- ## Src
    this folder containt the main code of the game. The main folder are actualy system, tools, and main. the others is just part of my game. if you want to make these for your template, you can delete the other folder. system contain the code to run the game and tools contain the scene and animation

# Flow of the  code
It begin from the main.cpp file. inside of this file will call a clas Game to run the game. inside of class Game you need to define and add your state. each state must be inherited from class state. if you want to use scene as a state make sure you inherite all the scene and state class. the game class also have a game state so you can shange state or scene. Game  class will run all the class state method like update, render, handle event, and next state. thats why you need this class to run the game. For more clear explanation you can look ath the diagram below.
    