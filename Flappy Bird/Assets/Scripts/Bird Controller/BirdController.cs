using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BirdController : MonoBehaviour
{
    public static BirdController instance;  //catch flag(synchronizing across the Scripts)
    public GameObject spawner;

    public float bounceForce;

    //status
    private bool isAlive;
    private bool didFlap;

    public float flag = 0;
    public int score = 0;

    //component
    private Rigidbody2D myBody;
    private Animator a;

    //audio
    [SerializeField]
    private AudioSource audioSource;

    [SerializeField]
    private AudioClip flyClip, pingClip, diedClip;

    // Use this for initialization
    void Awake()    //when declaring use Awake(), when doing sth use Start()
    {
        isAlive = true;
        myBody = GetComponent<Rigidbody2D>();
        a = GetComponent<Animator>();
        _MakeInstance();
        spawner = GameObject.Find("Spawner Pipe");
    }

    void _MakeInstance()
    {
        if (instance == null)
        {
            instance = this;
        }
    }

    // Update is called once per frame
    void FixedUpdate()      //when using physics( movement, jump, ...) use FixedUpdate() || when using tranform. ... use Update()
    {
        _BirdMovement();
    }

    void _BirdMovement()
    {
        if (isAlive)
        {
            if (didFlap)
            {
                didFlap = false;
                myBody.velocity = new Vector2(myBody.velocity.x, bounceForce);  //jump  (velocity {x, y})
                audioSource.PlayOneShot(flyClip);
            }
        }
        if (myBody.velocity.y > 0)
        {
            float angel = 0;
            angel = Mathf.Lerp(0, 90, myBody.velocity.y / 7);
            transform.rotation = Quaternion.Euler(0, 0, angel);     //rotate
        }
        else if (myBody.velocity.y == 0)
        {
            transform.rotation = Quaternion.Euler(0, 0, 0);         //rotate
        }
        else if (myBody.velocity.y < 0)
        {
            float angel = 0;
            angel = Mathf.Lerp(0, -90, -myBody.velocity.y / 7);
            transform.rotation = Quaternion.Euler(0, 0, angel);     //rotate
        }
    }

    public void _FlapButton()
    {
        didFlap = true;
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.tag == "PipeHolder")
        {
            score++;
            if (GamePlayController.instance != null)
            {
                GamePlayController.instance._SetScore(score);
            }
            audioSource.PlayOneShot(pingClip);
        }
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Pipe" || collision.gameObject.tag == "Ground")
        {
            flag = 1;
            if (isAlive)
            {
                isAlive = false;
                Destroy(spawner);
                audioSource.PlayOneShot(diedClip);
                a.SetTrigger("Died");
            }
            if(GamePlayController.instance != null)
            {
                GamePlayController.instance._ShowPanelWhenOver(score);
            }
        }
    }
}
