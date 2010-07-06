using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.IO;
using System.Security.AccessControl;
using System.Security.Principal;
using System.Windows.Forms;

using DependencyLibrary;
using SharpSvn;

namespace BoostDependency
{
    public partial class BoostDependencyControl : UserControl
    {        
        /// <summary>
        /// The DependencyDefinition describes the properties necessary to configure this dependency.
        /// </summary>
        private DependencyDefinition dependencyDefinition = new DependencyDefinition();
        
        public BoostDependencyControl()
        {
            InitializeComponent();

            propertyGrid1.SelectedObject = dependencyDefinition;
        }


        private void getSourceButton_Click(object sender, EventArgs e)
        {
            try
            {
                GetSource();
            }
            catch ( Exception exc )
            {
                MessageBox.Show( "An error occurred while trying to retrieve the source code.\n\n" + exc.ToString(), "Get Source Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Test to see of a particular directory is writeable by creating a temporary file and deleting it again.
        /// The function will thow an exception if this operation fails.
        /// </summary>
        /// <param name="directoryPath"></param>
        /// <returns></returns>
        private bool CanWrite(string directoryPath)
        {
            // First check that the directory exists
            if ( Directory.Exists(directoryPath) )
            {
                // Create a temporary file in the directory
                string tempFile = Path.GetFullPath(directoryPath) + Path.DirectorySeparatorChar + Guid.NewGuid().ToString() + ".tmp";
                FileStream file = File.Create(tempFile);
                file.Close();

                // Delete the file again
                File.Delete(tempFile);

                // If no exceptions occurred, then we safely write to this directory.
                return true;
            }
            return false;
        }

        /// <summary>
        /// Check to see if a particular directory path exists and is writable.
        /// </summary>
        /// <param name="directoryPath">The directory path to check.</param>
        /// <returns>True if the path is valid and writable.</returns>
        private bool CheckDirectory(string directoryPath, bool createIfNotExist )
        {
            if ( Directory.Exists(directoryPath) )
            {
                return CanWrite(directoryPath);                
            }
            else if (createIfNotExist)
            {
                // Create the directory if it does not exist.
                Directory.CreateDirectory(directoryPath);
                return CanWrite(directoryPath);
            }                 

            return false;
        }

        private void GetSource()
        {
            // Check if the directory exists and is writeable.
            if ( !CheckDirectory(dependencyDefinition.LocalPath,true) )
            {
                throw new DirectoryNotFoundException("The directory \"" + dependencyDefinition.LocalPath + "\" was not found or could not be created.");
            }

            // Make sure we can create a target to the SVN repository
            SvnTarget target;
            if ( !SvnTarget.TryParse(dependencyDefinition.SvnPath, out target) )
            {
                throw new Exception("The SVN path you've specified is not valid.  " +
                    "Please provide a valid URL or filesystem path pointing to " +
                    "a valid Subversion resource.");
            }

            using ( SvnClient client = new SvnClient() )
            {
                // Bind the GUI interface to the client
                SharpSvn.UI.SvnUI.Bind(client, this);


            }
        }
    }
}
