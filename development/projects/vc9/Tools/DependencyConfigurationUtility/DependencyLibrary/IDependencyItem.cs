using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Windows.Forms;

namespace DependencyLibrary
{
    /// <summary>
    /// Interface type to a dependency item.
    /// The dependency item is used to configure the 
    /// 3rd party dependencies used in our project.
    /// </summary>
    public interface IDependencyItem
    {
        /// <summary>
        /// The name of the dependency as it appears in the user interface.
        /// </summary>
        string Name
        {
            get;
        }

        /// <summary>
        /// A description that describes this dependency.
        /// This text will be used in the status text of the parent form.
        /// </summary>
        string Description
        {
            get;
        }

        /// <summary>
        /// A bitmap image icon that represents this dependency.
        /// </summary>
        Bitmap Icon
        {
            get;
        }

        Font Font
        {
            get;
        }

        /// <summary>
        /// Gets a Control object that will be used to configure and 
        /// execute this dependency's logic.
        /// </summary>
        Control Control
        {
            get;
        }
    }
}
