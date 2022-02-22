using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class HealthVisual : MonoBehaviour
{
    [SerializeField] Sprite heartFull;
    [SerializeField] Sprite heartEmpty;

    [SerializeField] PlayerStats playerstats;
    int maxhealth;
    int highscore;
    public EndMenu endMenu;
    public GameObject explosionparticle,explosionsound;

    List<GameObject> heartsList = new List<GameObject>();

    private void Start()
    {
        maxhealth = playerstats.getMaxHealth();
        initializeHealth(maxhealth);      
    }

    
    GameObject createHeart(Vector2 anchoredPos, int value)
    {
        GameObject heartGameObj = new GameObject("Heart", typeof(Image));

        heartGameObj.transform.SetParent(transform, false);

        heartGameObj.GetComponent<RectTransform>().anchoredPosition = anchoredPos;
        heartGameObj.GetComponent<RectTransform>().sizeDelta = new Vector2(20, 20);

        Image heartImg = heartGameObj.GetComponent<Image>();
        if (value == 0)
        {
            heartImg.sprite = heartEmpty;
        }
        else if (value == 1)
        {
            heartImg.sprite = heartFull;
        }       
        return heartGameObj;
    }
    
    void initializeHealth(int max)
    {
        int position = -50;
        for (int i = 0; i <max; i++)
        {
            heartsList.Add(createHeart(new Vector2(position, 0), 1));
            position -= -22;
        }
    }


    IEnumerator deathsequence()
    {

        yield return new WaitForSeconds(.4f);
        GameObject.Find("Main Camera").GetComponent<CameraFollow>().target = GameObject.FindGameObjectWithTag("Player").transform;
        yield return new WaitForSeconds(.7f);
        GameObject.FindGameObjectWithTag("Player").GetComponent<SpriteRenderer>().color = Color.black;
        Instantiate(explosionparticle, GameObject.FindGameObjectWithTag("Player").transform.position, Quaternion.identity);
        Instantiate(explosionsound, transform.position, Quaternion.identity);

        yield return new WaitForSeconds(.23f);
        SceneManager.LoadScene("end");


    }

    public void updateHealth()
    {

        int currentHealth = playerstats.getCurrentHealth();
        int maxHealth = playerstats.getMaxHealth();
        int position = -50;

        if (currentHealth <= 0)
        {
            Debug.Log("You died");
            StartCoroutine(deathsequence());
            
            
            for (int i = 0; i < maxhealth; i++)
            {
                heartsList[i] = createHeart(new Vector2(position, 0), 0);
                position -= -22;

            }
        }
        else if (currentHealth <= maxHealth)
        {
            {
                if (currentHealth > 0)
                {
                    for (int i = 0; i < currentHealth; i++)
                    {
                        heartsList[i] = createHeart(new Vector2(position, 0), 1);
                        //createHeart(new Vector2(position, 0), 1);
                        position -= -22;

                    }

                    for (int i = 0; i < maxHealth - currentHealth; i++)
                    {
                        heartsList[i] = createHeart(new Vector2(position, 0), 0);
                        //createHeart(new Vector2(position, 0), 0);
                        position -= -22;
                    }

                }
                
            }
        }




    }






}
