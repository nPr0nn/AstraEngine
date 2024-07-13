
### Development Guide for Astra 2D Game Engine

---

## Coding Conventions

0. Types renamed:
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

1. **Defines**:
    - Use UPPER_CASE with `_` separating the words.
    - Example:
      ```c
      #define MAX_BUFFER_SIZE 1024
      ``
       
2. **Typedef Variables**:
    - Use lowercase with all letters together.
    - Example:
      ```c
      typedef unsigned int u8;
      ```

3. **Variables**:
    - Use lower_case with `_` separating the words.
    - Example:
      ```c
      u8  screen_width;
      f32 delta_time;
      ```

4. **Functions**:
    - Use snake_case for function names.
    - `{` on the same line as the function name with no space between the name and the parenthesis.
    - Example:
      ```c
      void initialize_engine(){
          // function body
      }
      ```

5. **Structs**:
    - **Simple Structs (do not contain other structs inside it)**:
      - Use lower_case with `t_` before the name.
      - Examples:
        ```c
        typedef struct t_vec2 {
            f32 x;
            f32 y;
        } t_vec2;

        typedef struct t_rect {
            f32 x;
            f32 y;
            f32 width;
            f32 height;
        } t_rect;
        
        typedef struct t_circle {
            f32 x;
            f32 y;
            f32 radius;
        } t_circle;
        ``` 
    - **Composite Structs (contain other structs inside it)**:
      - Use CamelCase.
      - Examples:
        ```c
        typedef struct EngineContext {
            // other members
        } EngineContext;

        typedef struct Renderer {
            // other members
        } Renderer;
        ```
        
#### Directory Structure

#### Function Descriptions

#### Example Code Snippet

### Additional Notes

