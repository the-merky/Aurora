# ![Logo](cover.png)
<p align="center">
	<a href="https://github.com/ShambuKumar/Aurora/stargazers">
		<img alt="Stargazers" src="https://img.shields.io/github/stars/ShambuKumar/Aurora?style=for-the-badge&logo=starship&color=C9CBFF&logoColor=D9E0EE&labelColor=302D41">
  </a>
	<a href="https://github.com/ShambuKumar/Aurora/issues">
		<img alt="Issues" src="https://img.shields.io/github/issues/ShambuKumar/Aurora?style=for-the-badge&logo=gitbook&color=B5E8E0&logoColor=D9E0EE&labelColor=302D41">
  </a>
  <a href="https://github.com/ShambuKumar/Aurora/activity">
		<img alt="Activity" src="https://img.shields.io/github/commit-activity/m/ShambuKumar/Aurora?style=for-the-badge&logo=github&color=DDB6F2&logoColor=D9E0EE&labelColor=302D41">
  </a>
</p>
Aurora is an open-source chess engine being developed by Shambu Kumar in C++. 

## Goals :dart:

- **Chess Engine**: Aurora aims to be a powerful and fast chess engine.
- **Open Source**: The project is open-source, fostering collaboration and allowing developers to contribute, modify, and enhance the engine.
- **Neural Network**: The engine will use a neural network for evaluation. 
## Development Status :construction:

Please note that the Aurora Chess Engine project is currently a work in progress and not ready for use. Development is ongoing, and the engine is not yet fully functional.

## Contribution :raised_hands:

Contributions to the Aurora Chess Engine project are welcome once it reaches a more advanced state. If you're interested in contributing, please keep an eye on the repository for future updates and announcements.

## License :page_with_curl:

The project is under the MIT license

## Contact :email:

For any questions or inquiries about the Aurora Chess Engine project, please reach out to me at work@merky.dev

Thank you for your interest in Aurora Chess Engine. Stay tuned for future updates! :rocket:

## Begin worked on right now...
### Using UCI or making a dedicated GUI
### Move Search
### Special moves and rules
###
 - **En passant**
- **Castling**
- **Draws**
- **Castling rights**
###
## Note
If you want to follow what is being worked on exactly at the moment, feel free to check out the commits section!
# Documentation
### Note 
This section will cover how to chess engine works, and how to use it. This section may be updated less, because the main goal is to deliver a working chess engine, but this also helps to keep the project more organized!
## File structure
### The project consists of:
###
- **This README**
- **The MIT license**
- **An src folder**
which contains all code -this will be covered in detail in the other section
###
### Program overview
### The engine code consists of these 3 core parts
- **Move Generation: **
The computer gets all legal moves from a chess position
- **Move Search: **
Create a search tree of positions with a given depth
- **Evaluation: ** 
Give a chess position an evaluation score based pn which side is more likely to win

