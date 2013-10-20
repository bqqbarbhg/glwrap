glwrap
======

Description
-----------
Glwrap is a very lightweight wrapper over OpenGL 3.3.

Example
-------
```cpp
GLuint tex;
glGenTextures(1, &tex);
glBindTexture(GL_TEXTURE_2D, tex);
glTexParameteri(GL_TEXTURE_2D, GL_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_WRAP_T, GL_REPEAT);
glBindTexture(GL_TEXTURE_2D, 0);
glDeleteTextures(1, &tex);
```
```cpp
gl::Texture2D tex;
tex.Gen();
tex.Bind();
gl::BoundTexture2D().SetWrap(gl::Wrap(gl::REPAT, gl::REPEAT));
gl::BoundTexture2D().Unbind();
tex.Delete();
```
```cpp
auto tex = gl::OTexture2D::Create();
auto btex = tex.Bind();
btex.SetWrap(gl::Wrap::Repeat);
btex.Unbind();
```

Setup
-----
Include `glwrap.h` after OpenGL functions (and extension functions) are included. The library can be configured by defines. Example header (using GLEW):
```cpp
#ifndef GL_H_INCLUDED
#define GL_H_INCLUDED

#include <glew.h>
#include <GL/GL.h>

#ifdef _DEBUG
#define GLWRAP_FULL_DEBUG
#endif

#include <glwrap.h>

#endif
```
