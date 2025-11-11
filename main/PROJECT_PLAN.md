# Flappy Bird with Ultrasonic Sensor Project Plan

## Phase 1: Game Logic (No Hardware Yet)

1. **Set up the game environment**
   - Initialize display (LCD).
   - Draw a static bird and simple scrolling background or pipes.

2. **Basic bird movement**
   - Use a variable (e.g., `birdY`) to track the bird’s vertical position.
   - Add gravity so the bird falls over time.
   - Add a flap mechanic (e.g., button press makes bird go up).

3. **Pipes and scrolling**
   - Create pipes that move from right to left.
   - Randomize pipe gaps.
   - Reset pipes when they move off-screen.

4. **Collision detection**
   - End the game if the bird hits a pipe or goes off-screen.

5. **Score and reset**
   - Increase the score when the bird passes a pipe.
   - Add a "Game Over" screen and restart option.

---

## Phase 2: Ultrasonic Integration

6. **Connect and test ultrasonic sensor**
   - Verify the sensor outputs smooth distance readings (in cm).

7. **Map sensor readings to bird position**
   - Use `map()` to convert hand distance (e.g., 5–30 cm) to screen height.

8. **Replace button input with sensor**
   - Make the bird move based on hand distance instead of a button press.

---

## Phase 3: Polish

9. **Add visuals**
   - Improve sprites, motion smoothness, and scrolling background.

10. **Fine-tune controls**
    - Adjust distance sensitivity, gravity, and flap strength for better gameplay.

11. **Optional extras**
    - Add sound effects, LED indicators, or other feedback when scoring or colliding.
