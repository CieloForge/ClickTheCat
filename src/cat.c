#include <cat.h>
#include <raylib.h>
#include <raymath.h>

void DrawCat(int catX, int catY, Vector2 mousePos) {

    // Calculate eye positions based on mouse position
    int leftEyeX = catX - 25 + (mousePos.x - catX) / 10;
    int leftEyeY = catY - 5 + (mousePos.y - catY) / 10;
    int rightEyeX = catX + 25 + (mousePos.x - catX) / 10;
    int rightEyeY = catY - 5 + (mousePos.y - catY) / 10;

    // Clamp the pupil positions to stay within the black circles
    leftEyeX = Clamp(leftEyeX, catX - 25 - 6, catX - 25 + 6);
    leftEyeY = Clamp(leftEyeY, catY - 5 - 6, catY - 5 + 6);
    rightEyeX = Clamp(rightEyeX, catX + 25 - 6, catX + 25 + 6);
    rightEyeY = Clamp(rightEyeY, catY - 5 - 6, catY - 5 + 6);

    // Ensure the pupils stay within the black circles
    Vector2 leftEyeCenter = (Vector2){catX - 25, catY - 5};
    Vector2 rightEyeCenter = (Vector2){catX + 25, catY - 5};
    // Calculate direction to mouse with clamping
    Vector2 leftDir = Vector2Normalize(Vector2Subtract(mousePos, leftEyeCenter));
    Vector2 rightDir = Vector2Normalize(Vector2Subtract(mousePos, rightEyeCenter));

    // Limit pupil movement to stay within eye radius (6px)
    leftEyeX = (int)(leftEyeCenter.x + 6 * leftDir.x);
    leftEyeY = (int)(leftEyeCenter.y + 6 * leftDir.y);
    rightEyeX = (int)(rightEyeCenter.x + 6 * rightDir.x);
    rightEyeY = (int)(rightEyeCenter.y + 6 * rightDir.y);

    // Left Ear
    DrawTriangle((Vector2){catX - 70, catY - 75}, 
                    (Vector2){catX - 55, catY - 25}, 
                    (Vector2){catX - 20, catY - 45}, RED);
    // Left Inner Ear
    DrawTriangle((Vector2){catX - 65, catY - 65}, 
                    (Vector2){catX - 45, catY - 30}, 
                    (Vector2){catX - 25, catY - 40}, PINK);

    // Right Ear
    DrawTriangle((Vector2){catX + 20, catY - 45}, 
                    (Vector2){catX + 55, catY - 25}, 
                    (Vector2){catX + 70, catY - 75}, RED);
    // Right Inner Ear
    DrawTriangle((Vector2){catX + 25, catY - 40}, 
                    (Vector2){catX + 45, catY - 30}, 
                    (Vector2){catX + 65, catY - 65}, PINK);

    // DRAW HEAD (Ellipse)
    DrawEllipse(catX, catY, 65, 50, RED);

    // DRAW EYES (Circles)
    // Left Eye Outer
    DrawCircle(catX - 25, catY - 5, 9, BLACK);
    DrawCircle(leftEyeX, leftEyeY, 3, WHITE); // Reflection
    
    // Right Eye Outer
    DrawCircle(catX + 25, catY - 5, 9, BLACK);
    DrawCircle(rightEyeX, rightEyeY, 3, WHITE); // Reflection

    // DRAW CHEEKS (Circles)
    DrawCircle(catX - 35, catY + 12.5, 6, PINK);
    DrawCircle(catX + 35, catY + 12.5, 6, PINK);

    // DRAW NOSE (Triangle)
    DrawTriangle((Vector2){catX - 5, catY + 5}, 
                    (Vector2){catX, catY + 10}, 
                    (Vector2){catX + 5, catY + 5}, PINK);

    // DRAW MOUTH (Lines/Arcs)
    DrawCircleSector((Vector2){catX - 6, catY + 12.5}, 6, 0, 180, 16, BLACK);
    DrawCircleSector((Vector2){catX - 6, catY + 12.5}, 4.5, 0, 180, 16, RED); // Masking
    
    DrawCircleSector((Vector2){catX + 6, catY + 12.5}, 6, 0, 180, 16, BLACK);
    DrawCircleSector((Vector2){catX + 6, catY + 12.5}, 4.5, 0, 180, 16, RED); // Masking

    // DRAW WHISKERS (Lines)
    // Left Whiskers
    DrawLineEx((Vector2){catX - 50, catY + 5}, (Vector2){catX - 80, catY + 2.5}, 2, BLACK);
    DrawLineEx((Vector2){catX - 50, catY + 10}, (Vector2){catX - 85, catY + 7.5}, 2, BLACK);
    DrawLineEx((Vector2){catX - 50, catY + 15}, (Vector2){catX - 90, catY + 12.5}, 2, BLACK); // Additional whisker
    DrawLineEx((Vector2){catX - 50, catY + 20}, (Vector2){catX - 95, catY + 17.5}, 2, BLACK); // Additional whisker

    // Right Whiskers
    DrawLineEx((Vector2){catX + 50, catY + 5}, (Vector2){catX + 80, catY + 2.5}, 2, BLACK);
    DrawLineEx((Vector2){catX + 50, catY + 10}, (Vector2){catX + 85, catY + 7.5}, 2, BLACK);
    DrawLineEx((Vector2){catX + 50, catY + 15}, (Vector2){catX + 90, catY + 12.5}, 2, BLACK); // Additional whisker
    DrawLineEx((Vector2){catX + 50, catY + 20}, (Vector2){catX + 95, catY + 17.5}, 2, BLACK); // Additional whisker
}