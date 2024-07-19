
### Development Guide for Astra 2D Game Engine

---

## Coding Conventions
Every part of the game engine should follow these coding conventions.

0. Use C99 standard

1. ast_[thing] for functions and structs

2. Types renamed:
    - `uint8_t` : `u8`
    - `uint16_t` : `u16`
    - `uint32_t` : `u32`
    - `uint64_t` : `u64`
    - `int8_t` : `i8`
    - `int16_t` : `i16`
    - `int32_t` : `i32`
    - `int64_t` : `i64`
    - `float` : `f32`
    - `double` : `f64`

3. **Defines**:
    - Use UPPER_CASE with `_` separating the words.
    - Example:
      ```c
      #define MAX_BUFFER_SIZE 1024
      ``
       
4. **Typedef Variables**:
    - Use lowercase with all letters together.
    - Example:
      ```c
      typedef unsigned int u8;
      ```

5. **Variables**:
    - Use lower_case with `_` separating the words.
    - Example:
      ```c
      u8  screen_width;
      f32 delta_time;
      ```

6. **Functions**:
    - Use snake_case for function names.
    - `{` on the same line as the function name with no space between the name and the parenthesis.
    - Example:
      ```c
      void astra_engine_init(){
          // function body
      }
      ```

7. **Structs**:
    - **Simple Structs (do not contain other structs inside it)**:
      - Use lower_case
      - Examples:
        ```c
        typedef struct astra_vec2 {
            f32 x;
            f32 y;
        } astra_vec2;

        typedef struct astra_rect {
            f32 x;
            f32 y;
            f32 width;
            f32 height;
        } astra_rect;
        
        typedef struct astra_circle {
            f32 x;
            f32 y;
            f32 radius;
        } astra_circle;
        ``` 
    - **Composite Structs (contain other structs inside it)**:
      - Use CamelCase.
      - Examples:
        ```c
        typedef struct astra_EngineContext {
            // other members
        } astra_EngineContext;

        typedef struct astra_Renderer {
            // other members
        } astra_Renderer;
        ```
        
#### Directory Structure

#### Function Descriptions

#### Example Code Snippet

### Additional Notes

