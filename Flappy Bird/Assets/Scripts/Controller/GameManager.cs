using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour {

    public static GameManager instance;

    private const string HIGH_SCORE = "High Score";

    private void Awake()
    {
        _MakeSingleInstance();
        _IsFirstTimeStarted();
    }

    void _IsFirstTimeStarted()
    {
        if (!PlayerPrefs.HasKey("IsFirstTimeStarted"))
        {
            PlayerPrefs.SetInt(HIGH_SCORE, 0);
            PlayerPrefs.SetInt("IsFirstTimeStarted", 0);
        }
    }

    void _MakeSingleInstance()
    {
        if(instance != null)
        {
            Destroy(gameObject);
        }
        else
        {
            instance = this;
            DontDestroyOnLoad(gameObject);
        }
    }

    public void _SetHighScore(int score)
    {
        PlayerPrefs.SetInt(HIGH_SCORE, score);
    }

    public int _GetHighScore()
    {
        return PlayerPrefs.GetInt(HIGH_SCORE);
    }
}
