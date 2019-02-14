using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GamePlayController : MonoBehaviour
{

    public static GamePlayController instance;

    [SerializeField]
    private Button insButton;

    [SerializeField]
    private Text scoreText, currentScoreText, HighScoreText;

    [SerializeField]
    private GameObject gameOverPanel, pausePanel;

    private void Awake()
    {
        Time.timeScale = 0;
        _MakeInstance();
    }

    void _MakeInstance()
    {
        if (instance == null)
        {
            instance = this;
        }
    }

    public void _InstructionButton()
    {
        Time.timeScale = 1;
        insButton.gameObject.SetActive(false);
    }

    public void _SetScore(int score)
    {
        scoreText.text = "" + score;
    }

    public void _ShowPanelWhenOver(int score)
    {
        gameOverPanel.SetActive(true);
        currentScoreText.text = "" + score;
        if(score > GameManager.instance._GetHighScore())
        {
            GameManager.instance._SetHighScore(score);
        }
        HighScoreText.text = "" + GameManager.instance._GetHighScore();
    }

    public void _MenuButton()
    {
        SceneManager.LoadScene("MainMenu");
    }

    public void _RestartButton()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex);
    }

    public void _PauseButton()
    {
        Time.timeScale = 0;
        pausePanel.SetActive(true);
    }

    public void _ResumeButton()
    {
        Time.timeScale = 1;
        pausePanel.SetActive(false);
    }
}
