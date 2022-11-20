# ue-restyle
## Motivation
I did really want to see new design for blueprints in ue-5, but that didn't happen. 

My manically configured part couldn't handle seeing blurry background.png anymore  

So i decided to take the responsibility and remake it :) 
<details>
  <summary>Spoiler</summary>
  It took a half of a year lmao 
</details> 


## Features
Plugin is made of 3 factory providers which represents factories inside of FEdGraphUtilities, which are used by engine to spawn Nodes, Pins, Connections.

### General
- New SVG icons
- New widgets
- Almost everything is configurable with styles (Colors, Spacings, Sizes, Brushes, Buttons...)

### Nodes
- 3 States (Normal, Selected, Invalid)
- New title style 
- Ability to disable "Target Is"

### Variable Nodes
- Ability to hide "GET" title [Optional]

### Compact Nodes
- New title style with ability to apply it if title length exceeds <n>
- Background icons for Function and Macro

### Reroute
- Shows "drag" boundaries on hover

### Comments
- New resizing method (which prevents cursor slide off comment)
- Opacity level is set by default (For normal, selected states)

### Comment Bubbles (Its not bubble)
- Buttons shows only if widget is hovered

### Node Reports (error/warning etc.) and State (development/disabled)
- Title is configurable

### Pin Connections
- New style for wires, featuring 45° & 90° alignment
- Prioritizing in context of input/output pins for line length and/or position 
(Works for left->right & right->left transitions, also exec<->reroute have their own prioritization)

- Squared, rounded corners
- Radius (up to 0.5 of length, visually shortens the path)
- Optimized for backward routing (has snap points)

### Pins
- Custom colors [Optional]
- Custom pin-constructors (Vector4 is only available atm)
  <details>
  <summary>Thoughts</summary>
    Maybe having pin constructors for structures with short constructors isn't that bad
  </details> 
- Vector that is Rotator may use new labels (RPY) [Optional]
- Custom text for "Add Pin" [Optional]
### Zoom [Optional]
- Ability to set or even generate zoom behavior

## Recommendations (likely to change)
Windows OC, because MinHook library (i get used to) doesn't support other systems. It's used to redesign CreateWidget node. Thats probably all atm.
You can run it anyway on any other system, just this widget will be with unreal style.


## Restrictions or Why what was made was needed

### Technical Side
To apply on "design" behavior of SGraphNode/SGraphPin classes, the new ones needed to be created.

Because some of them are not exported for external use, it becomes impossible to mantain the inheritance;

In simple words. All SGraphNodes are still SGraphNodes, but all SGraphNodeK2 are now S**Default**GraphNodeK2, 
and all logic inside of SGraphNodeK2 was explicitly (manually by hand) copied to Restyle's classes.

**For each logical update on widgets made in newer versions of Unreal, the plugin must be updated in order to match them**

### User Experience
Do not try to change settings while working with graphs. Close them, make a change and only then open. 
Otherwise, editor will crash (due to style changes)

Having opened "Editor Settings" window with restyle loaded may cause editor to slow down. (For some reason slate processess non-visible options) 
 

## FAQ
### **What type of plugin is this?**
DeveloperTool that waits for Editor to be loaded in order to load itself.

### **Could it break my data?** 
There is a possibility, but it's not that univocal. 

SGraphPin writes values to UEdGraphPin and some of such functions of course are copies of originals. Non-original writings made for Enum, Custom pins. 

It will break if non-updated plugin is used for Unreal Engine version containing non-backward compatibility behavioral code.
As such breaking scenario isn't happen only due to external problems, i expect you to understand the volatility of engine itself and have some backups 
(in case you have not experienced yet the failure of loosing weekly work: blueprint backup system in engine is not a solution) 

### **I have my own factories defined, will it work?**
Plugin registers factories at Index 0 and they check if there is any other factory wants to spawn that UClass. 
So yes it will work, but styles will mismatch (ways of fixing this part are not discussed nor done yet)
