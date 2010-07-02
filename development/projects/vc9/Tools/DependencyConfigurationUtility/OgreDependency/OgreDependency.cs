using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

using DependencyLibrary;

namespace OgreDependency
{
    public class OgreDependency : IDependencyItem
    {
        private string name = "Ogre";
        private string description = "Ogre3D Graphics Renderer";
        private Bitmap icon = Properties.Resources.ogre_logo_64x64;
        private Font font = new Font("Candara", 27.75f, FontStyle.Bold);
        private Control control = null;

        public string Name
        {
            get
            {
                return name;
            }
        }

        public string Description
        {
            get
            {
                return description;
            }
        }

        public Bitmap Icon
        {
            get
            {
                return icon;
            }
        }

        public Font Font
        {
            get 
            {
                return font;
            }
        }

        public Control Control
        {
            get 
            {
                return control;
            }
        }
    }
}
