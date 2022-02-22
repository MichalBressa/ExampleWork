using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class NavMeshAI : MonoBehaviour
{
    public List<Transform> Waypoints;
    [SerializeField]  private int waypointIndex = 0;

    public Transform tempObj;

    static NavMeshAI _navmeshai;

    public Transform player;

    public static bool isPatrolling = true;

    [SerializeField] private Vector3 directionPosition;

    private NavMeshAgent agent;

    private void Awake()
    {
        Transform[] points = GameObject.Find("Waypoints").GetComponentsInChildren<Transform>();

        for(int i=1;i < points.Length;i++)
        {
            Waypoints.Add(points[i]) ;
        }

        tempObj = points[points.Length-1];

        agent = GetComponent<NavMeshAgent>();
        SetTarget(Waypoints[waypointIndex]);
        player = GameObject.FindGameObjectWithTag("Player").transform;
        _navmeshai = this;

    }


    private void Update()
    {

        agent.destination = directionPosition;

        if (isPatrolling)
        {
            Patrol();
            agent.stoppingDistance = 0f;
        }
        else
        {
            SetTarget(player);
            agent.stoppingDistance = 1.5f;
        }
        
    }





    public bool RandomBool()
    {
        if (Random.value < 0.25f)
        {
            return true; // if true -> skip one waypoint
        }
        else
        {
            return false;   // false -> continue as normal
        }
    }

    // ---------------------------------------------------------------
    // REMEMBER TO ADJUST NUMBERS ACORDING TO THE LENGHT OF THE LIST |
    // ---------------------------------------------------------------

    
    public void Patrol()
    {
        SetTarget(Waypoints[waypointIndex]);

        if (Vector3.Distance(transform.position, directionPosition) <= 0.5f)
        {
            

            if (RandomBool())
            {
                waypointIndex += 2;
                
            }
            else
            {
                waypointIndex++;
            }
            

            if (waypointIndex >= Waypoints.Count - 2)
            {
                waypointIndex = 0;
                SetTarget(Waypoints[waypointIndex]);

                return;
            }
            else
            {
                SetTarget(Waypoints[waypointIndex]);
            }
        }
    }




    public void SetTarget(Transform target)
    {
        if (target != null)
        {
            directionPosition = target.position;
            
        }
        else
        {
            directionPosition = Waypoints[waypointIndex].position;
        }

    }

    Vector3 tempTransform;
    
    public static void GetLastPos()
    {
        // change agent destination

        _navmeshai.tempTransform = GetPlayerPos();
        _navmeshai.tempObj.transform.position = _navmeshai.tempTransform;

        //_navmeshai.Waypoints[4] = _navmeshai.tempObj.transform;

        _navmeshai.waypointIndex = 4;


        // Debug.Log("After set target");

    }


    public static Vector3 GetPlayerPos()
    {
        return _navmeshai.player.transform.position;
    }


}
