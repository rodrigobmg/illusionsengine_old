using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using DependencyLibrary;
using BoostDependency;
using OgreDependency;


namespace DependencyConfigurationUtility
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            // TODO: Load these dependency types dynamically
            dependencyList.Items.Add(new BoostDependency.BoostDependency() );
            dependencyList.Items.Add(new OgreDependency.OgreDependency() );
        }

        protected override void OnClosing(CancelEventArgs e)
        {
            // Allow the dependency items to save their settings.
            foreach( IDependencyItem item in dependencyList.Items )
            {
                if ( item != null )
                {
                    item.SaveSettings();
                }
            }
        }

        private void dependencyList_DrawItem(object sender, DrawItemEventArgs e)
        {
            // If the item is the selected item, then draw the rectangle
            // filled in blue. The item is selected when a bitwise And  
            // of the State property and the DrawItemState.Selected 
            // property is true.
            if ((e.State & DrawItemState.Selected) == DrawItemState.Selected)
            {
                Color color1 = Color.White;
                Color color2 = Color.FromArgb(192,210,238);

                ColorBlend colorBlend = new ColorBlend();

                colorBlend.Positions = new Single[] { 0.0f, 1.0f };
                colorBlend.Colors = new Color[] { color1, color2 };

                LinearGradientBrush gradientBrush = new LinearGradientBrush(e.Bounds, Color.Black, Color.White, LinearGradientMode.Vertical);
                gradientBrush.InterpolationColors = colorBlend;

                e.Graphics.FillRectangle(gradientBrush, e.Bounds);

                // Draw the border
                Pen selectionBorder = new Pen(Color.Black, 3.0f);
                selectionBorder.DashStyle = DashStyle.Dash;
                Rectangle itemBounds = e.Bounds;

                itemBounds.X += 1;
                itemBounds.Y += 1;
                itemBounds.Width -= 3;
                itemBounds.Height -= 3;

                e.Graphics.DrawRectangle(selectionBorder, itemBounds);
            }
            else
            {
                // Otherwise, draw the rectangle filled in beige.
                Color color1 = Color.White;
                Color color2 = Color.FromArgb(193, 192, 168);

                ColorBlend colorBlend = new ColorBlend();

                colorBlend.Positions = new Single[] { 0.0f, 1.0f };
                colorBlend.Colors = new Color[] { color1, color2 };

                LinearGradientBrush gradientBrush = new LinearGradientBrush(e.Bounds, Color.Black, Color.White, LinearGradientMode.Vertical);
                gradientBrush.InterpolationColors = colorBlend;

                e.Graphics.FillRectangle(gradientBrush, e.Bounds);

            }


            object item = dependencyList.Items[e.Index];
            if ( item is IDependencyItem )
            {
                IDependencyItem dependencyItem = item as IDependencyItem;
                Bitmap icon = dependencyItem.Icon;
                string name = dependencyItem.Name;
                Font font = dependencyItem.Font;

                Rectangle imageBounds = e.Bounds;

                imageBounds.X += 3;
                imageBounds.Y += 3;
                imageBounds.Size = icon.Size;

                Rectangle labelBounds = imageBounds;
                labelBounds.X += imageBounds.Size.Width + 3;
                labelBounds.Size = e.Bounds.Size;

                StringFormat labelFormat = new StringFormat();
                labelFormat.Alignment = StringAlignment.Near;
                labelFormat.LineAlignment = StringAlignment.Center;

                e.Graphics.DrawImage(icon, imageBounds );
                e.Graphics.DrawString(name, font, Brushes.Black, labelBounds, labelFormat);

            }
            else
            {
                // Draw the text in the item.
                e.Graphics.DrawString(dependencyList.Items[e.Index].ToString(),
                    this.Font, Brushes.Black, e.Bounds.X, e.Bounds.Y);

            }

            //// Draw the focus rectangle around the selected item.
            //e.DrawFocusRectangle();

        }

        private void dependencyList_MeasureItem(object sender, MeasureItemEventArgs e)
        {
            e.ItemHeight = 74;
        }

        private void dependencyList_SelectedIndexChanged(object sender, EventArgs e)
        {
            object item = dependencyList.SelectedItem;
            
            if ( item is IDependencyItem )
            {
                IDependencyItem dependencyItem = item as IDependencyItem;
                toolStripStatusLabel1.Text = dependencyItem.Description;

                splitContainer1.Panel2.Controls.Clear();
                splitContainer1.Panel2.Controls.Add(dependencyItem.Control);
                if ( dependencyItem.Control != null )
                {
                    dependencyItem.Control.Dock = DockStyle.Fill;
                }

            }
            else
            {
                toolStripStatusLabel1.Text = item.ToString();
            }
        }
    }
}
