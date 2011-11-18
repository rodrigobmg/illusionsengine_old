/**
 * @file: GraphicsSubsystem.hpp
 * @date: September 18, 2009
 * 
 * The GraphicsSubsystem is used to create and manage the graphics renderer.
 *
 */

#ifndef ILL_GRAPHICS_GRAPHICSSUBSYSTEM_HPP
#define ILL_GRAPHICS_GRAPHICSSUBSYSTEM_HPP

#include <Ill/Core/Subsystem.hpp>
#include <Ill/Core/Application.fwd.hpp>
#include <Ill/Graphics/GraphicsTypes.hpp>

namespace Ill
{
    namespace Graphics
    {
        class GraphicsRenderer;

        class GRAPHICS_DLL GrapicsSubsystem : public Ill::Core::Subsystem
        {
        public:

            CLASS( GrapicsSubsystem, Ill::Core::Subsystem );
            CONSTRUCTOR( GRAPHICS_DLL, public, GrapicsSubsystem, () );

            /**
            * Startup the graphics subsystem.
            */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, bool, Startup, ( const Ill::Core::PropertyMap& startupOptions ) );
       
            /**
            * Shutdown
            */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, bool, Shutdown, () );

            /**
             * Retrieve a pointer to the GraphicsRenderer implementation.
             * @precondition The subsystem must have been initialized before
             * you can get a pointer to the GraphicsRenderer implementation.
             */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, GraphicsRenderer*, GetGraphicsRenderer, () );

        protected:

            /**
            * Populate my defined properties from the passed-in property map
            */
            VIRTUAL_METHOD( GRAPHICS_DLL, public, void, SetProperties, (const Ill::Core::PropertyMap& properties) );

        private:
            // Getters and setters for property types
            const std::wstring& get_GraphicsLibName() const
            {
                return m_GraphicsLibName;
            }
            void set_GraphicsLibName( const std::wstring& libName )
            {
                m_GraphicsLibName = libName;
            }

            // Data members
            // The name of graphics library that is used to load the graphics renderer.
            std::wstring        m_GraphicsLibName;

            GraphicsRenderer*   m_pGraphicsRenderer;

        public:
            // Define properties at the bottom of the class to avoid VAssistX getting confused and hiding 
            // my member variables from using code-completion.
            PROPERTY( GRAPHICS_DLL, const std::wstring&, GraphicsLibName );
        };
    }
}

#endif // ILL_GRAPHICS_GRAPHICSSUBSYSTEM_HPP