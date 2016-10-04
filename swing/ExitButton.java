//
// Gabin Marignier - élève en 2e année à Télécom ParisTech - 2016
//

import javax.swing.JButton;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

///
/// Bouton permettant de quitter le programme
///
public class ExitButton extends JButton implements MouseListener {
	private static final long serialVersionUID = 4211787640825327199L;

	public ExitButton(String name)
	{
		super(name);
		this.addMouseListener(this);
	}
	
	@Override
	public void mouseClicked(MouseEvent arg0) {
		System.exit(0);
	}

	@Override
	public void mouseEntered(MouseEvent arg0) {}

	@Override
	public void mouseExited(MouseEvent arg0) {}

	@Override
	public void mousePressed(MouseEvent arg0) {}

	@Override
	public void mouseReleased(MouseEvent arg0) {}
}
