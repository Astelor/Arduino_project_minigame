## An Arduino Project
this README is written and under development(+ the project itself) by *Astelor*

## Table of Contents
[Purpose](##Purpose)
[How to Play](##How%20to%20Play)
   [nAnB](###nAnB)
   [Guess the Number](##Guess%20the%20Number)

## Purpose
>This is my first Arduino project coded with vscode, so there might be some bugs lurking somewhere underneath a leaf.

This project is a minigame device, with max7219 7 segment display(8 digits), and a 4x4 Keypad. Designed to perform simple number based games

## How To Play
Since it's a ~~crappy~~ mini game device, a manual of instructions must be provided.
### nAnB
1. When in `[======]` menu, press `A` for nAnB
2. You have infinite guesses for the game, type in the answer using the 3x3 numberpad, use `*` as backspace and `#` as submitting the answer
   > Every number from 0~9 can appear more than once, for example:`9999` and `0909` can be a generated answer key.
4. If the answer is incorrect, it'll display the number of `A` and `B`. Repeat step 2 unitil you have the correct answer. `A` means you submitted the correct number on the correct digit, `B` means you submitted the correct number, but it's on the wrong digit.
3. if the answer is correct, it'll display `4A0B` for 1 second before returning to the menu

> If you want to know the answer key before solving it yourself, press `A`, the answer key will show up for 1 second before returning to the menu.

> If you want to play the game again, just press `A`, it'll generate another answer key and start a new game. 
### Guess the Number
*tba*

