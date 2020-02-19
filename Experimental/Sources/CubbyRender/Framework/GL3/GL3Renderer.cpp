/*************************************************************************
> File Name: GLRenderer.h
> Project Name: CubbyFlow
> This code is based on Jet Framework that was created by Doyub Kim.
> References: https://github.com/doyubkim/fluid-engine-dev
> Purpose: abstract Renderer class implemented with Modern OpenGL
> Created Time: 2020/02/18
> Copyright (c) 2020, Ji-Hong snowapril
*************************************************************************/
#include <Framework/GL3/GL3Renderer.h>
#include <Core/Utils/Logging.h>
#include <GL/gl3w.h>

namespace CubbyFlow {
namespace CubbyRender {
    
        GL3Renderer::GL3Renderer()
        {
            //! Do nothing
        }

        GL3Renderer::~GL3Renderer()
        {
            //! Do nothing
        }

        int GL3Renderer::initializeGL()
        {
            if (gl3wInit())
            {
                CUBBYFLOW_ERROR << "Failed to initialize OpenGL";
                return -1;
            }

            if (!gl3wIsSupported(3, 3))
            {
                CUBBYFLOW_ERROR << "Your hardware does not support OpenGL 3.3";
                return -1;
            }

            return 0;
        }
} 
}