# Table of Contents
- [Table of Contents](#table-of-contents)
- [Layout](#layout)
- [How To Play](#how-to-play)
  - [nAnB](#nanb)
  - [Guess the number](#guess-the-number)
# Layout
![image](https://github.com/Astelor/Arduino_project_minigame/blob/main/Misc/arduino%20layout.png)
# How To Play
The following list is how you can play the games step by step.
## nAnB

1. When you're in `[======]` `MENU`, press `A` to start the game.


2. You have infinite guesses for the game, type the answer by the 3x3 numberpad.
   > Every number from, 0~9, can appear more than once, for example: `9999` and `0909` can be a possible answer key.

3. `*` is backspace, and `#` is submitting a 4-digit answer.


4. If the answer is incorrect, it'll display the amount of `A`s and `B`s. Keep trying unitil you get `4A0B`. 
   >`A` means you submitted a correct number on the correct digit, `B` means you submitted a correct number, but it's on the wrong digit.


5. if the answer is correct, it'll display `4A0B` and a cool `victory animation` before returning to the `MENU`.


6. To see the previous `A` and `B` result, press `D`, it will appear on the screen. Press `D` again to return to your current inputs.


7. To get the answer key directly, press `C`, it will appear on the screen. Press `C` again to return to the `MENU`.

> If you want to play the game again, just press `A` again, it'll generate another answer key and start a new game. 

## Guess the number
1. When you're in `[======]` `MENU`, press `B` to start the game.
   >the user input rules are the same for both games, you can skip to step 4

2. You have infinite guesses for the game, type the answer by the 3x3 numberpad.


3. `*` is backspace, and `*` is submitting an answer.


4. If the answer is `out-of-range`, an `out-of-range` animation will apear, before showing you the current `range` of numbers. The starting `range` is `1~1000`.
   > for example: if the current range is `15~888`, if the answer is `15`, `888`, larger than `888`, or smaller than `15`, the answer is `out-of-range`

5. If the answer is incorrect, the cooresponding `range` will appear. Keep trying until you get the correct number.


6. If the answer is correct, a cool `victory animation` will appear on the screen before returning to the `MENU`.

7. To see the current `range`, press `D`, it will appear on the screen. Press `D` again to return to your current inputs.

8. To get the answer key directly, press `C`, it will appear on the screen. Press `C` again to return to the `MENU`.

