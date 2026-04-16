#define GLLD_IMPLEMENTATION
#include "./../../glld.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>



static const GLchar *g_vertex_glsl =
"#version 330 core\n"
"\n"
"layout (location=0)\n"
"in vec3 a_pos;\n"
"\n"
"void main() {\n"
"   gl_Position = vec4(a_pos, 1.0);\n"
"}\n";


static const GLchar *g_fragment_glsl =
"#version 330 core\n"
"\n"
"out vec4 f_col;\n"
"\n"
"void main() {\n"
"   f_col = vec4(1.0, 1.0, 1.0, 1.0);\n"
"}\n";


GLfloat g_vertices[] = {
    -0.5, -0.5, 0.0,
    -0.5,  0.5, 0.0,
     0.5, -0.5, 0.0,
     0.5,  0.5, 0.0
};


GLuint  g_indices[] = {
    0, 1, 2,
    1, 2, 3
};



class Shader {
    private:
        GLuint m_id;

    public:
        
        /* constructors... */

        Shader(void);

        Shader(const Shader &);

        ~Shader(void);

        const Shader &operator = (const Shader &);

        /* accessors... */

        GLuint getID(void) const;

        /* public methods... */

        int bind(void) const;

        int unbind(void) const;

        int setVertexShader(const GLchar *) const;

        int setFragmentShader(const GLchar *) const;
};
        
/* constructors... */

Shader::Shader(void) : m_id(glCreateProgram()) { }

Shader::Shader(const Shader &other) : m_id(other.m_id) { }

Shader::~Shader(void) {
    glDeleteProgram(this->m_id);
    this->m_id = 0;
}

const Shader &Shader::operator = (const Shader &other) {
    this->m_id = other.m_id;
    return (*this);
}

/* accessors... */

GLuint Shader::getID(void) const {
    return (this->m_id);
}

int Shader::bind(void) const {
    glUseProgram(this->m_id);
    
    /* get errors... */
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        return (err);
    }

    /* success... */
    return (GL_NO_ERROR);
}

/* public methods... */

int Shader::unbind(void) const {
    glUseProgram(0);
    
    /* get errors... */
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        return (err);
    }

    /* success... */
    return (GL_NO_ERROR);
}

int Shader::setVertexShader(const GLchar *code) const {
    /* compile... */
    GLuint shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &code, 0);
    glCompileShader(shader);

    /* link... */
    glAttachShader(this->m_id, shader);
    glLinkProgram(this->m_id);

    /* success... */
    return (GL_NO_ERROR);
}

int Shader::setFragmentShader(const GLchar *code) const {
    /* compile... */
    GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, &code, 0);
    glCompileShader(shader);

    /* link... */
    glAttachShader(this->m_id, shader);
    glLinkProgram(this->m_id);

    /* success... */
    return (GL_NO_ERROR);
}



class Buffer {
    private:
        GLuint m_id;

    public:
        
        /* constructors... */

        Buffer(void);

        Buffer(const Buffer &);
        
        ~Buffer(void);

        /* accessors... */

        const Buffer &operator = (const Buffer &);

        GLuint getID(void) const;
        
        GLsizei getSize(void) const;

        /* public methods... */

        int setData(void *, const size_t);
        
        int setSubData(void *, const size_t, const size_t);
        
        int setStorage(void *, const size_t);
};
        
/* constructors... */

Buffer::Buffer(void) : m_id(0) { glCreateBuffers(1, &this->m_id); }

Buffer::Buffer(const Buffer &other) : m_id(other.m_id) { }

Buffer::~Buffer(void) {
    glDeleteBuffers(1, &this->m_id);
    this->m_id = 0;
}

const Buffer &Buffer::operator = (const Buffer &other) {
    this->m_id = other.m_id;
    return (*this);
}

/* accessors... */

GLuint Buffer::getID(void) const {
    return (this->m_id);
}

GLsizei Buffer::getSize(void) const {
    GLsizei size = 0;
    glGetNamedBufferParameteriv(this->m_id, GL_BUFFER_SIZE, &size);
    
    /* get errors... */
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        return (0);
    }
    
    /* success... */
    return (size);
}

/* public methods... */

int Buffer::setData(void *data, const size_t size) {
    /* set data... */
    glNamedBufferData(this->m_id, size, data, GL_STATIC_DRAW);
    
    /* get errors... */
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        return (err);
    }

    /* success... */
    return (GL_NO_ERROR);
}

int Buffer::setSubData(void *data, const size_t size, const size_t offset) {
    /* set data... */
    glNamedBufferSubData(this->m_id, offset, size, data);
    
    /* get errors... */
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        return (err);
    }

    /* success... */
    return (GL_NO_ERROR);
}

int Buffer::setStorage(void *data, const size_t size) {
    /* set storage... */
    glNamedBufferStorage(this->m_id, size, data, GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
    
    /* get errors... */
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        return (err);
    }

    /* success... */
    return (GL_NO_ERROR);
}



class VertexArray {
    private:
        GLuint m_id;

    public:
        
        /* constructors... */

        VertexArray(void);

        VertexArray(const VertexArray &);

        ~VertexArray(void);

        const VertexArray &operator = (const VertexArray &);

        /* accessors... */

        GLuint getID(void) const;

        /* public methods... */

        int bind(void) const;

        int unbind(void) const;

        int setVertexBuffer(const Buffer &, const size_t, const size_t, const size_t) const;
        
        int setIndexBuffer(const Buffer &) const;

        int setLayout(const size_t, const size_t, const size_t, const size_t) const;
};
        
/* constructors... */

VertexArray::VertexArray(void) : m_id(0) { glCreateVertexArrays(1, &this->m_id); }

VertexArray::VertexArray(const VertexArray &other) : m_id(other.m_id) { }

VertexArray::~VertexArray(void) {
    glDeleteVertexArrays(1, &this->m_id);
    this->m_id = 0;
}

const VertexArray &VertexArray::operator = (const VertexArray &other) {
    this->m_id = other.m_id;
    return (*this);
}

/* accessors... */

GLuint VertexArray::getID(void) const {
    return (this->m_id);
}

int VertexArray::bind(void) const {
    glBindVertexArray(this->m_id);
    
    /* get errors... */
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        return (err);
    }

    /* success... */
    return (GL_NO_ERROR);
}

/* public methods... */

int VertexArray::unbind(void) const {
    glBindVertexArray(0);
    
    /* get errors... */
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        return (err);
    }

    /* success... */
    return (GL_NO_ERROR);
}

int VertexArray::setVertexBuffer(const Buffer &buffer, const size_t bindingindex, const size_t offset, const size_t stride) const {
    glVertexArrayVertexBuffer(this->m_id, bindingindex, buffer.getID(), offset, stride);
    
    /* get errors... */
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        return (err);
    }

    /* success... */
    return (GL_NO_ERROR);
}

int VertexArray::setIndexBuffer(const Buffer &buffer) const {
    glVertexArrayElementBuffer(this->m_id, buffer.getID());
    
    /* get errors... */
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        return (err);
    }

    /* success... */
    return (GL_NO_ERROR);
}

int VertexArray::setLayout(const size_t layout, const size_t index, const size_t size, const size_t offset) const {
    glEnableVertexArrayAttrib(this->m_id, layout);
    
    /* get errors... */
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        return (err);
    }
    
    glVertexArrayAttribBinding(this->m_id, layout, index);
    
    /* get errors... */
    err = glGetError();
    if (err != GL_NO_ERROR) {
        return (err);
    }
    
    glVertexArrayAttribFormat(this->m_id, layout, size, GL_FLOAT, GL_FALSE, offset);
    
    /* get errors... */
    err = glGetError();
    if (err != GL_NO_ERROR) {
        return (err);
    }

    /* success... */
    return (GL_NO_ERROR);
}



int main(void) {
    if (!SDL_Init(SDL_INIT_VIDEO)) { return (1); }
    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4)) { return (1); }
    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6)) { return (1); }
    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE)) { return (1); }

    SDL_Window *window = SDL_CreateWindow("glld.h - C++ sample", 800, 600, SDL_WINDOW_OPENGL);
    if (!window) { return (1); }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) { return (1); }

    if (!SDL_GL_MakeCurrent(window, context)) { return (1); }
    if (!glldLoadGLLoader((t_glldLoader) SDL_GL_GetProcAddress)) { return (1); }
    
    Shader shader;
    shader.setVertexShader(g_vertex_glsl);
    shader.setFragmentShader(g_fragment_glsl);
    
    Buffer vbo, ibo;
    vbo.setData(g_vertices, sizeof(g_vertices));
    ibo.setData(g_indices, sizeof(g_indices));

    VertexArray vao;
    vao.setLayout(0, 0, 3, 0 * sizeof(GLfloat));
    vao.setVertexBuffer(vbo, 0, 0, 3 * sizeof(GLfloat));
    vao.setIndexBuffer(ibo);

    for (int exit = 0; !exit; ) {
        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();
        vao.bind();

        glDrawElements(GL_TRIANGLES, ibo.getSize() / sizeof(GLuint), GL_UNSIGNED_INT, 0);

        vao.unbind();
        shader.unbind();

        SDL_GL_SwapWindow(window);
        
        SDL_Event event = { 0 };
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case (SDL_EVENT_QUIT): { exit = 1; } break;
            }
        }
    }

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return (0);
}
