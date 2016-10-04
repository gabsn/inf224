//
// Gabin Marignier - élève en 2e année à Télécom ParisTech - 2016
//

import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JTextArea;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

///
/// Bouton permettant de faire apparaître une fenêtre de dialogue pour naviguer sur la set-top box
///
public class TextButton extends JButton implements MouseListener{
	private static final long serialVersionUID = 1L;
	private JTextArea textArea;
	private Client client;
	private String command;

	public TextButton(String command, JTextArea textArea, Client client) {
		super(command);
		this.client = client;
		this.textArea = textArea;
		this.command = command;
		this.addMouseListener(this);
	}

	@Override
	public void mouseClicked(MouseEvent arg0) {
		try {
			if (command == "Find media") {
				String request = JOptionPane.showInputDialog("Which media are you looking for ?");
				String response = client.send("find "+request);
				textArea.append(response+'\n');
			} else if (command == "Play media") {
				String request = JOptionPane.showInputDialog("Which media do you want to play ?");
				String response = client.send("play "+request);
				textArea.append(response+'\n');
			} else {
				System.exit(0);
			}
		}
		catch (Exception e) {
			textArea.append(e.getMessage());
			return;
		}
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
