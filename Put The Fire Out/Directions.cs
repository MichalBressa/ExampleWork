using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Directions : MonoBehaviour
{
    public Transform target;
    public float hideDist = 3f;
    public GameObject[] fireArray;
    [SerializeField] GameObject directionArrowObj;


    void FixedUpdate()
    {
        fireArray = GameObject.FindGameObjectsWithTag("Fire");

        if (fireArray.Length < 1 )
        {
            directionArrowObj.SetActive(false);
        }
        else
        {
            directionArrowObj.SetActive(true);
        

            

            target = GetClosestFire(fireArray);

            // target = GetClosestFire(Transform[] fires)
            var direction = target.position - transform.position;

            if (direction.magnitude < hideDist)
            {
                 SetChildrenActive(false);
            }
            else
            {
                SetChildrenActive(true);
                var angle = Mathf.Atan2(direction.y, direction.x) * Mathf.Rad2Deg;
                transform.rotation = Quaternion.AngleAxis(angle, Vector3.forward);

            }

        }
    }


    void SetChildrenActive(bool value)
    {
        foreach (Transform child in transform)
        {
            child.gameObject.SetActive(value);
        }
    }

    
    	Transform GetClosestFire(GameObject[] firesA)
	    {
	    Transform closestFire = null;
	    float minDist = Mathf.Infinity;
	    Vector3 currentPos = transform.position;
	    foreach (GameObject fireObj in firesA)
	    {
	        float dist = Vector3.Distance(fireObj.transform.position, currentPos);
	        if (dist<minDist)
	        {
                closestFire = fireObj.transform;
	            minDist = dist;
            }
        }
            return closestFire;
        }

    








}
